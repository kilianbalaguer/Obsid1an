import Link from "next/link";

export const metadata = {
  title: "Obsid1an — Installation Guide",
  description: "How to install Obsid1an on iOS 27.0 – 27.0.1",
};

function Callout({
  type,
  children,
}: {
  type: "tip" | "warning" | "danger";
  children: React.ReactNode;
}) {
  const styles = {
    tip: { border: "rgba(100, 200, 120, 0.4)", bg: "rgba(100, 200, 120, 0.08)", label: "TIP", color: "#6fc87a" },
    warning: { border: "rgba(255, 200, 50, 0.4)", bg: "rgba(255, 200, 50, 0.08)", label: "WARNING", color: "#e8c840" },
    danger: { border: "rgba(255, 80, 80, 0.4)", bg: "rgba(255, 80, 80, 0.08)", label: "DANGER", color: "#ff6b6b" },
  };
  const s = styles[type];
  return (
    <div
      className="guide-callout"
      style={{ borderLeftColor: s.border, backgroundColor: s.bg }}
    >
      <span className="guide-callout-label" style={{ color: s.color }}>
        {s.label}
      </span>
      {children}
    </div>
  );
}

export default function GuidePage() {
  return (
    <main className="guide-page">
      <nav className="guide-nav">
        <Link href="/" className="guide-back">
          ← Back
        </Link>
        <span style={{ width: 1, height: 16, background: "rgba(255,255,255,0.15)" }} />
        <span className="guide-nav-title">Installation Guide</span>
      </nav>

      <article className="guide-content">
        <h1>Installing Obsid1an</h1>
        <p className="guide-intro">
          Obsid1an is a rootful jailbreak for iOS 27.0 – 27.0.1, powered by
          the calif.io kernel exploit. This guide walks you through sideloading
          and running the jailbreak on your device.
        </p>

        <Callout type="warning">
          <p>
            Obsid1an is a <strong>semi-untethered</strong> jailbreak. After
            rebooting your device, you will need to re-run the app to
            re-enable the jailbreak.
          </p>
        </Callout>

        <Callout type="danger">
          <p>
            If you have another jailbreak installed, you must restore to a
            clean iOS 27.0 or 27.0.1 firmware before installing Obsid1an.
            Running multiple jailbreaks will cause conflicts.
          </p>
        </Callout>

        {/* Requirements */}
        <h2 id="requirements">Requirements</h2>
        <ul>
          <li>A device running iOS 27.0 or 27.0.1</li>
          <li>A computer (Mac, Windows, or Linux)</li>
          <li>A sideloading tool — any of the following:
            <ul>
              <li>AltStore / AltServer</li>
              <li>Sideloadly</li>
              <li>Impactor</li>
            </ul>
          </li>
          <li>The Obsid1an .ipa file</li>
        </ul>

        {/* Downloads */}
        <h2 id="downloads">Downloads</h2>
        <div className="guide-downloads">
          <a
            href="https://github.com/kilianbalaguer/Obsid1an/releases/latest"
            target="_blank"
            rel="noopener noreferrer"
            className="guide-download-btn"
          >
            Download Obsid1an .ipa
          </a>
        </div>
        <Callout type="tip">
          <p>
            Always download the latest release from GitHub to make sure you
            have the most up-to-date version with bug fixes.
          </p>
        </Callout>

        {/* Sideloading */}
        <h2 id="sideloading">Sideloading the App</h2>
        <ol>
          <li>Download the Obsid1an .ipa from the link above.</li>
          <li>Open your sideloading tool of choice (AltStore, Sideloadly, Impactor, etc.).</li>
          <li>Connect your device to your computer via USB.</li>
          <li>Select the Obsid1an .ipa file and sideload it to your device.</li>
          <li>Wait for the installation to complete.</li>
        </ol>
        <Callout type="tip">
          <p>
            If you are using AltStore, the app will be valid for 7 days. You
            will need to refresh it before it expires using AltServer on your
            computer.
          </p>
        </Callout>

        {/* Trusting */}
        <h2 id="trusting">Trusting the App</h2>
        <ol>
          <li>
            Open <strong>Settings</strong> → <strong>General</strong> →{" "}
            <strong>VPN & Device Management</strong>.
          </li>
          <li>
            Find the developer profile associated with your sideloading
            account and tap <strong>Trust</strong>.
          </li>
        </ol>
        <Callout type="warning">
          <p>
            On some devices this menu may be labeled{" "}
            <strong>Profiles & Device Management</strong> instead.
          </p>
        </Callout>

        {/* Running */}
        <h2 id="running">Running Obsid1an</h2>
        <ol>
          <li>Reboot your device before running the jailbreak for the first time.</li>
          <li>Open the Obsid1an app from your home screen.</li>
          <li>
            Tap the <strong>Jailbreak</strong> button and wait for the exploit
            to run. You will see real-time logs as it progresses.
          </li>
          <li>
            Once complete, your device will respring and the jailbreak will be
            active.
          </li>
        </ol>
        <Callout type="tip">
          <p>
            If the app crashes or the exploit fails, simply reboot your device
            and try again. The calif.io exploit may require a few attempts.
          </p>
        </Callout>
        <Callout type="danger">
          <p>
            Do not lock your device or switch apps while the exploit is
            running. Wait for the process to fully complete.
          </p>
        </Callout>

        {/* Package Managers */}
        <h2 id="package-managers">Installing Tweaks</h2>
        <p>
          After jailbreaking, Obsid1an will set up your package manager of
          choice. During the initial setup, you can choose between:
        </p>
        <ul>
          <li>
            <strong>Sileo</strong> (recommended) — a modern, fast package
            manager
          </li>
          <li>
            <strong>Zebra</strong> — a lightweight alternative
          </li>
        </ul>
        <p>
          Open your chosen package manager to browse and install tweaks. Since
          Obsid1an is rootful, most traditional tweaks should work without
          needing special rootless builds.
        </p>

        {/* After reboot */}
        <h2 id="after-reboot">After a Reboot</h2>
        <p>
          Since Obsid1an is semi-untethered, a reboot will put your device
          back in a non-jailbroken state. To re-enable:
        </p>
        <ol>
          <li>Open the Obsid1an app.</li>
          <li>Tap <strong>Jailbreak</strong> again.</li>
          <li>Wait for the exploit and respring to complete.</li>
        </ol>
        <p>
          All your tweaks and settings will be preserved — you just need to
          re-run the exploit.
        </p>

        <div className="guide-footer-nav">
          <Link href="/" className="guide-back-link">
            ← Back to Obsid1an
          </Link>
        </div>
      </article>
    </main>
  );
}
