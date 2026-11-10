import Foundation

@Observable
final class JailbreakSettings {
    static let shared = JailbreakSettings()

    private let defaults = UserDefaults.standard
    private let basePath = "/var/mobile/Library"

    var autoRespring: Bool {
        didSet { defaults.set(autoRespring, forKey: "autoRespring") }
    }

    var verboseLog: Bool {
        didSet { defaults.set(verboseLog, forKey: "verboseLog") }
    }

    var loadTweaks: Bool {
        didSet {
            defaults.set(loadTweaks, forKey: "loadTweaks")
            syncTweakFlag()
        }
    }

    var hideJailbreak: Bool {
        didSet { defaults.set(hideJailbreak, forKey: "hideJailbreak") }
    }

    var safeMode: Bool {
        didSet {
            defaults.set(safeMode, forKey: "safeMode")
            syncSafeModeFlag()
        }
    }

    private init() {
        self.autoRespring = defaults.object(forKey: "autoRespring") as? Bool ?? true
        self.verboseLog = defaults.object(forKey: "verboseLog") as? Bool ?? false
        self.loadTweaks = defaults.object(forKey: "loadTweaks") as? Bool ?? true
        self.hideJailbreak = defaults.object(forKey: "hideJailbreak") as? Bool ?? true
        self.safeMode = defaults.object(forKey: "safeMode") as? Bool ?? false
    }

    // MARK: - Flag files (read by the tweak loader at injection time)

    private func syncTweakFlag() {
        let flag = "\(basePath)/.obsid1an_no_tweaks"
        if loadTweaks {
            unlink(flag)
        } else {
            FileManager.default.createFile(atPath: flag, contents: nil)
        }
    }

    private func syncSafeModeFlag() {
        let flag = "\(basePath)/.obsid1an_safe_mode"
        if safeMode {
            FileManager.default.createFile(atPath: flag, contents: nil)
        } else {
            unlink(flag)
        }
    }

    // MARK: - Tool actions

    func refreshIconCache() {
        var pid: pid_t = 0
        let argv: [UnsafeMutablePointer<CChar>?] = [
            strdup("/usr/bin/uicache"),
            strdup("-a"),
            nil
        ]
        defer { argv.forEach { free($0) } }
        posix_spawn(&pid, "/usr/bin/uicache", nil, nil, argv, nil)
    }

    func reinstallBootstrap() {
        Task {
            await BootstrapManager.install { _ in }
        }
    }

    func enterSafeMode() {
        safeMode = true
        RespringManager.restartSpringBoard()
    }

    func exitSafeMode() {
        safeMode = false
        RespringManager.restartSpringBoard()
    }
}
