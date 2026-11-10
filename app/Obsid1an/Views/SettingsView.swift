import SwiftUI
import UIKit

private struct ShareSheet: UIViewControllerRepresentable {
    let text: String
    func makeUIViewController(context: Context) -> UIActivityViewController {
        UIActivityViewController(activityItems: [text], applicationActivities: nil)
    }
    func updateUIViewController(_ vc: UIActivityViewController, context: Context) {}
}

struct SettingsView: View {
    @Binding var isPresented: Bool
    @State private var settings = JailbreakSettings.shared
    @State private var showExportSheet = false
    @State private var exportText = ""

    var body: some View {
        VStack(spacing: 0) {
            HStack {
                Text("Settings")
                    .font(.system(size: 24, weight: .bold, design: .rounded))
                    .foregroundStyle(.white)
                Spacer()
                Button {
                    withAnimation(.spring(duration: 0.35)) {
                        isPresented = false
                    }
                } label: {
                    Image(systemName: "xmark")
                        .font(.system(size: 13, weight: .bold))
                        .foregroundStyle(.white.opacity(0.6))
                        .frame(width: 28, height: 28)
                        .background(.white.opacity(0.15), in: Circle())
                }
            }
            .padding(.horizontal, 24)
            .padding(.top, 24)
            .padding(.bottom, 8)

            ScrollView(.vertical, showsIndicators: false) {
                VStack(spacing: 24) {
                    settingsSection("EXPLOIT") {
                        settingsToggle("Auto Respring", icon: "arrow.2.circlepath", isOn: $settings.autoRespring)
                        settingsToggle("Verbose Logging", icon: "terminal", isOn: $settings.verboseLog)
                        settingsRow("Exploit", icon: "cpu", trailing: "calif.io")
                    }

                    settingsSection("ENVIRONMENT") {
                        settingsToggle("Hide Jailbreak", icon: "eye.slash.fill", isOn: $settings.hideJailbreak)
                        settingsToggle("Load Tweaks", icon: "puzzlepiece.extension.fill", isOn: $settings.loadTweaks)
                        settingsToggle("Safe Mode", icon: "shield.fill", isOn: $settings.safeMode)
                    }

                    settingsSection("TOOLS") {
                        settingsAction("Refresh Icon Cache", icon: "app.dashed") {
                            settings.refreshIconCache()
                        }
                        settingsAction("Reinstall Bootstrap", icon: "arrow.down.circle") {
                            settings.reinstallBootstrap()
                        }
                        settingsAction("Export Logs", icon: "square.and.arrow.up") {
                            exportText = ExploitManager.lastLogs.joined(separator: "\n")
                            showExportSheet = true
                        }
                    }

                    settingsSection("DEVICE") {
                        settingsRow("Model", icon: "iphone", trailing: deviceModel)
                        settingsRow("iOS", icon: "gear", trailing: UIDevice.current.systemVersion)
                        settingsRow("Version", icon: "diamond.fill", trailing: appVersion)
                    }

                    settingsSection("CREDITS") {
                        creditLink("Kilian Balaguer", role: "Developer", url: "https://github.com/kilianbalaguer")
                        creditLink("calif.io", role: "Kernel Exploit", url: "https://calif.io")
                    }

                    Text("Obsid1an v\(appVersion)")
                        .font(.system(size: 12, weight: .medium))
                        .foregroundStyle(.white.opacity(0.25))
                        .padding(.top, 4)
                        .padding(.bottom, 8)
                }
                .padding(.top, 12)
            }
            .frame(maxHeight: 480)
            .padding(.bottom, 16)
        }
        .frame(maxWidth: 340)
        .glassEffect(.regular, in: .rect(cornerRadius: 32))
        .sheet(isPresented: $showExportSheet) {
            ShareSheet(text: exportText)
        }
    }

    // MARK: - Components

    private func settingsSection<Content: View>(_ title: String, @ViewBuilder content: () -> Content) -> some View {
        VStack(alignment: .leading, spacing: 2) {
            Text(title)
                .font(.system(size: 12, weight: .semibold))
                .foregroundStyle(.white.opacity(0.35))
                .tracking(1)
                .padding(.horizontal, 24)
                .padding(.bottom, 6)

            VStack(spacing: 0) {
                content()
            }
            .padding(.horizontal, 16)
        }
    }

    private func settingsToggle(_ title: String, icon: String, isOn: Binding<Bool>) -> some View {
        HStack(spacing: 12) {
            Image(systemName: icon)
                .font(.system(size: 14))
                .foregroundStyle(.white.opacity(0.6))
                .frame(width: 22)
            Text(title)
                .font(.system(size: 15, weight: .medium))
                .foregroundStyle(.white)
            Spacer()
            Toggle("", isOn: isOn)
                .labelsHidden()
                .tint(Color(.displayP3, red: 0.494, green: 0.515, blue: 1.0))
        }
        .padding(.horizontal, 14)
        .padding(.vertical, 11)
    }

    private func settingsRow(_ title: String, icon: String, trailing: String) -> some View {
        HStack(spacing: 12) {
            Image(systemName: icon)
                .font(.system(size: 14))
                .foregroundStyle(.white.opacity(0.6))
                .frame(width: 22)
            Text(title)
                .font(.system(size: 15, weight: .medium))
                .foregroundStyle(.white)
            Spacer()
            Text(trailing)
                .font(.system(size: 14))
                .foregroundStyle(.white.opacity(0.4))
        }
        .padding(.horizontal, 14)
        .padding(.vertical, 11)
    }

    private func settingsAction(_ title: String, icon: String, action: @escaping () -> Void) -> some View {
        Button(action: action) {
            HStack(spacing: 12) {
                Image(systemName: icon)
                    .font(.system(size: 14))
                    .foregroundStyle(.white.opacity(0.6))
                    .frame(width: 22)
                Text(title)
                    .font(.system(size: 15, weight: .medium))
                    .foregroundStyle(.white)
                Spacer()
                Image(systemName: "chevron.right")
                    .font(.system(size: 12, weight: .semibold))
                    .foregroundStyle(.white.opacity(0.25))
            }
        }
        .padding(.horizontal, 14)
        .padding(.vertical, 11)
    }

    private func creditLink(_ name: String, role: String, url: String) -> some View {
        Button {
            if let link = URL(string: url) {
                UIApplication.shared.open(link)
            }
        } label: {
            HStack {
                Text(name)
                    .font(.system(size: 15, weight: .semibold))
                    .foregroundStyle(.white.opacity(0.85))
                Spacer()
                Text(role)
                    .font(.system(size: 13))
                    .foregroundStyle(.white.opacity(0.4))
                Image(systemName: "arrow.up.right")
                    .font(.system(size: 11, weight: .semibold))
                    .foregroundStyle(.white.opacity(0.3))
            }
        }
        .padding(.horizontal, 14)
        .padding(.vertical, 8)
    }

    // MARK: - Helpers

    private var appVersion: String {
        Bundle.main.infoDictionary?["CFBundleShortVersionString"] as? String ?? "1.0.0"
    }

    private var deviceModel: String {
        var size = 0
        sysctlbyname("hw.machine", nil, &size, nil, 0)
        var machine = [CChar](repeating: 0, count: size)
        sysctlbyname("hw.machine", &machine, &size, nil, 0)
        return String(cString: machine)
    }
}
