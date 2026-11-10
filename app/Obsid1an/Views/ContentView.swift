import SwiftUI

struct ContentView: View {
    @State private var showSettings = false
    @State private var exploitManager = ExploitManager()
    @State private var logExpanded = false

    private var isSupported: Bool { CalifExploit.checkCompatibility() }

    var body: some View {
        ZStack {
            NavigationStack {
                ZStack {
                    LinearGradient(
                        colors: [
                            Color(.displayP3, red: 0.49365, green: 0.51451, blue: 1.0),
                            Color(.displayP3, red: 0.51696, green: 0.16413, blue: 0.54559)
                        ],
                        startPoint: .top,
                        endPoint: UnitPoint(x: 0.5, y: 0.7)
                    )
                    .ignoresSafeArea()

                    VStack(spacing: 0) {
                        VStack(spacing: logExpanded ? 6 : 12) {
                            Image("Obsid1an")
                                .resizable()
                                .aspectRatio(contentMode: .fit)
                                .frame(
                                    width: logExpanded ? 48 : 88,
                                    height: logExpanded ? 48 : 88
                                )
                                .clipShape(RoundedRectangle(
                                    cornerRadius: logExpanded ? 12 : 22,
                                    style: .continuous
                                ))
                                .shadow(color: .black.opacity(0.3), radius: 20, y: 8)

                            VStack(spacing: 3) {
                                Text("Obsid1an")
                                    .font(.system(
                                        size: logExpanded ? 20 : 34,
                                        weight: .bold,
                                        design: .rounded
                                    ))
                                    .foregroundStyle(.white)

                                HStack(spacing: 5) {
                                    Text("iOS \(exploitManager.deviceVersion)")
                                    Text("·")
                                    Text(isSupported ? "Supported" : "Unsupported")
                                        .foregroundStyle(
                                            isSupported ? .green : .red
                                        )
                                }
                                .font(.system(size: logExpanded ? 12 : 14, weight: .medium, design: .rounded))
                                .foregroundStyle(.white.opacity(0.55))
                            }

                            if !logExpanded {
                                Text("\(CalifExploit.name) · \(exploitManager.statusLabel)")
                                    .font(.system(size: 12, weight: .medium, design: .monospaced))
                                    .foregroundStyle(.white.opacity(0.35))
                                    .transition(.opacity)
                            }
                        }
                        .padding(.top, logExpanded ? 4 : 80)

                        Spacer(minLength: logExpanded ? 12 : 0)

                        actionArea
                            .padding(.horizontal, logExpanded ? 16 : 48)
                            .padding(.bottom, logExpanded ? 16 : 48)
                    }
                }
                .toolbar {
                    ToolbarItem(placement: .topBarLeading) {
                        Menu {
                            Button("Restart SpringBoard", systemImage: "arrow.trianglehead.2.counterclockwise") {
                                RespringManager.restartSpringBoard()
                            }
                            Button("Reboot Userspace", systemImage: "arrow.clockwise") {
                                RespringManager.rebootUserspace()
                            }
                        } label: {
                            Image(systemName: "arrow.2.circlepath")
                        }
                    }
                    ToolbarItem(placement: .topBarTrailing) {
                        Button {
                            withAnimation(.spring(duration: 0.4)) {
                                showSettings = true
                            }
                        } label: {
                            Image(systemName: "gearshape.fill")
                        }
                    }
                }
            }

            if showSettings {
                Color.black.opacity(0.4)
                    .ignoresSafeArea()
                    .onTapGesture {
                        withAnimation(.spring(duration: 0.35)) {
                            showSettings = false
                        }
                    }
                    .transition(.opacity)

                SettingsView(isPresented: $showSettings)
                    .transition(.scale(scale: 0.92).combined(with: .opacity))
            }
        }
    }

    // MARK: - Action area (morphs between button and log)

    @ViewBuilder
    private var actionArea: some View {
        VStack(spacing: 0) {
            if logExpanded {
                ScrollViewReader { proxy in
                    ScrollView(.vertical, showsIndicators: false) {
                        VStack(alignment: .leading, spacing: 3) {
                            ForEach(
                                Array(exploitManager.logs.enumerated()),
                                id: \.offset
                            ) { i, line in
                                Text(line)
                                    .font(.system(size: 12.5, design: .monospaced))
                                    .foregroundStyle(
                                        line.hasPrefix("[!]")
                                            ? .red.opacity(0.9)
                                            : .white.opacity(0.7)
                                    )
                                    .id(i)
                            }
                        }
                        .padding(16)
                        .frame(maxWidth: .infinity, alignment: .leading)
                    }
                    .onChange(of: exploitManager.logs.count) {
                        if let last = exploitManager.logs.indices.last {
                            withAnimation(.easeOut(duration: 0.2)) {
                                proxy.scrollTo(last, anchor: .bottom)
                            }
                        }
                    }
                }

                if !exploitManager.isRunning {
                    Button {
                        withAnimation(.spring(duration: 0.5, bounce: 0.12)) {
                            logExpanded = false
                        }
                    } label: {
                        Text(exploitManager.status == .done ? "Done" : "Dismiss")
                            .font(.system(size: 15, weight: .semibold, design: .rounded))
                            .foregroundStyle(.white)
                            .padding(.horizontal, 28)
                            .padding(.vertical, 10)
                    }
                    .glassEffect(.regular, in: .capsule)
                    .padding(.bottom, 14)
                    .transition(.identity)
                }
            } else {
                Text(exploitManager.buttonLabel)
                    .font(.system(size: 18, weight: .bold, design: .rounded))
                    .foregroundStyle(.white)
                    .padding(.horizontal, 40)
                    .padding(.vertical, 16)
                    .transition(.identity)
            }
        }
        .clipShape(.rect(cornerRadius: logExpanded ? 20 : 28))
        .frame(maxWidth: logExpanded ? .infinity : nil)
        .frame(maxHeight: logExpanded ? .infinity : nil)
        .glassEffect(.regular, in: .rect(cornerRadius: logExpanded ? 20 : 28))
        .contentShape(Rectangle())
        .onTapGesture {
            guard !logExpanded, !exploitManager.isRunning else { return }
            withAnimation(.spring(duration: 0.6, bounce: 0.15)) {
                logExpanded = true
            }
            Task { await exploitManager.run() }
        }
    }
}

#Preview {
    ContentView()
}
