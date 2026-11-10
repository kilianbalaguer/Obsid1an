import Foundation

enum RespringManager {

    // MARK: - Respring (kill SpringBoard → launchd restarts it)

    static func restartSpringBoard() {
        var pid: pid_t = 0
        let argv: [UnsafeMutablePointer<CChar>?] = [
            strdup("/usr/bin/killall"),
            strdup("-9"),
            strdup("SpringBoard"),
            nil
        ]
        defer { argv.forEach { free($0) } }

        let ret = posix_spawn(&pid, "/usr/bin/killall", nil, nil, argv, nil)
        if ret != 0 {
            NSLog("[Obsid1an] respring failed: posix_spawn returned %d", ret)
        }
    }

    // MARK: - Userspace reboot (restarts all userspace without kernel reboot)

    static func rebootUserspace() {
        var pid: pid_t = 0
        let argv: [UnsafeMutablePointer<CChar>?] = [
            strdup("/usr/bin/launchctl"),
            strdup("reboot"),
            strdup("userspace"),
            nil
        ]
        defer { argv.forEach { free($0) } }

        let ret = posix_spawn(&pid, "/usr/bin/launchctl", nil, nil, argv, nil)
        if ret != 0 {
            NSLog("[Obsid1an] userspace reboot failed: posix_spawn returned %d", ret)
        }
    }
}
