import Foundation

enum BootstrapManager {

    static let basePath = "/var/jb"
    static let sourcesDir = "\(basePath)/etc/apt/sources.list.d"
    static let sileoConfig = "\(basePath)/etc/sileo.json"

    // MARK: - Bootstrap extraction

    static func install(log: @escaping (String) -> Void) async -> Bool {
        guard let tarball = Bundle.main.path(forResource: "bootstrap", ofType: "tar.zst") else {
            log("[!] Bootstrap tarball not found in bundle")
            return false
        }

        log("[*] Extracting bootstrap to \(basePath)…")
        let ok = spawn("/usr/bin/tar", args: ["-xf", tarball, "-C", "/"])
        guard ok else {
            log("[!] Bootstrap extraction failed")
            return false
        }

        log("[+] Bootstrap extracted")

        log("[*] Preparing dpkg database…")
        _ = spawn("/var/jb/usr/bin/dpkg", args: ["--configure", "-a"])
        log("[+] dpkg configured")

        log("[*] Writing Obsid1an repo…")
        writeDefaultSources()
        writeSileoConfig()
        log("[+] Repo configured")

        log("[*] Refreshing APT…")
        _ = spawn("/var/jb/usr/bin/apt-get", args: ["update", "-o", "Dir::Etc::sourcelist=\(sourcesDir)"])
        log("[+] APT refreshed")

        return true
    }

    // MARK: - Default repo (non-removable)

    static func writeDefaultSources() {
        let obsid1anRepo = """
        Types: deb
        URIs: https://repo.obsid1an.app/
        Suites: ./
        Components:

        """

        let procursusRepo = """
        Types: deb
        URIs: https://apt.procurs.us/
        Suites: 2700
        Components: main

        """

        writeFile(at: "\(sourcesDir)/obsid1an.sources", content: obsid1anRepo)
        writeFile(at: "\(sourcesDir)/procursus.sources", content: procursusRepo)
    }

    static func writeSileoConfig() {
        let config = """
        {
            "defaultRepos": [
                "https://repo.obsid1an.app/"
            ],
            "lockedRepos": [
                "https://repo.obsid1an.app/"
            ]
        }
        """
        writeFile(at: sileoConfig, content: config)
    }

    // MARK: - Package installation

    static func installDeb(at path: String, log: @escaping (String) -> Void) -> Bool {
        log("[*] Installing \(URL(fileURLWithPath: path).lastPathComponent)…")
        let ok = spawn("/var/jb/usr/bin/dpkg", args: ["-i", path])
        if ok {
            log("[+] Installed")
        } else {
            log("[!] Installation failed")
        }
        return ok
    }

    // MARK: - Helpers

    @discardableResult
    private static func spawn(_ path: String, args: [String]) -> Bool {
        var pid: pid_t = 0
        let argv: [UnsafeMutablePointer<CChar>?] = ([path] + args).map { strdup($0) } + [nil]
        defer { argv.forEach { free($0) } }
        let ret = posix_spawn(&pid, path, nil, nil, argv, nil)
        guard ret == 0 else { return false }
        var status: Int32 = 0
        waitpid(pid, &status, 0)
        return status == 0
    }

    private static func writeFile(at path: String, content: String) {
        let dir = (path as NSString).deletingLastPathComponent
        FileManager.default.createFile(atPath: dir, contents: nil)
        try? FileManager.default.createDirectory(atPath: dir, withIntermediateDirectories: true)
        try? content.write(toFile: path, atomically: true, encoding: .utf8)
    }
}
