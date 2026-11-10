export default function Home() {
  return (
    <>
      {/* Hero */}
      <section className="hero-section">
        <div>
          {/* eslint-disable-next-line @next/next/no-img-element */}
          <img
            src="/icon.png"
            alt="Obsid1an Icon"
            className="hero-icon"
          />
          <h1 className="hero-title">Obsid1an</h1>
          <h2 className="hero-subtitle">iOS 27.0 – 27.0.1</h2>
        </div>
        <div className="buttons-row">
          <a
            className="download-button primary-button"
            href="https://github.com/kilianbalaguer/Obsid1an/releases/latest"
            target="_blank"
            rel="noopener noreferrer"
          >
            Download .ipa
          </a>
          <a className="download-button secondary-button" href="/guide">
            Installation Guide
          </a>
          <a
            className="contact-button"
            href="https://github.com/kilianbalaguer/Obsid1an"
            target="_blank"
            rel="noopener noreferrer"
            aria-label="GitHub"
          >
            <svg
              fill="#FFFFFF"
              xmlns="http://www.w3.org/2000/svg"
              viewBox="0 0 30 30"
              width="30"
              height="30"
            >
              <path d="M15,3C8.373,3,3,8.373,3,15c0,5.623,3.872,10.328,9.092,11.63C12.036,26.468,12,26.28,12,26.047v-2.051 c-0.487,0-1.303,0-1.508,0c-0.821,0-1.551-0.353-1.905-1.009c-0.393-0.729-0.461-1.844-1.435-2.526 c-0.289-0.227-0.069-0.486,0.264-0.451c0.615,0.174,1.125,0.596,1.605,1.222c0.478,0.627,0.703,0.769,1.596,0.769 c0.433,0,1.081-0.025,1.691-0.121c0.328-0.833,0.895-1.6,1.588-1.962c-3.996-0.411-5.903-2.399-5.903-5.098 c0-1.162,0.495-2.286,1.336-3.233C9.053,10.647,8.706,8.73,9.435,8c1.798,0,2.885,1.166,3.146,1.481C13.477,9.174,14.461,9,15.495,9 c1.036,0,2.024,0.174,2.922,0.483C18.675,9.17,19.763,8,21.565,8c0.732,0.731,0.381,2.656,0.102,3.594 c0.836,0.945,1.328,2.066,1.328,3.226c0,2.697-1.904,4.684-5.894,5.097C18.199,20.49,19,22.1,19,23.313v2.734 c0,0.104-0.023,0.179-0.035,0.268C23.641,24.676,27,20.236,27,15C27,8.373,21.627,3,15,3z" />
            </svg>
          </a>
        </div>
      </section>

      {/* Info — "Obsid1an is..." */}
      <section className="info-section dark-section">
        <PhoneMockup screenshot="/screenshot_home.png" alt="Obsid1an home screen" />
        <div>
          <div>
            <h3>Obsid1an is...</h3>
            <ul>
              <li>A jailbreak for iOS 27.0 – 27.0.1</li>
              <li>Powered by the calif.io kernel exploit</li>
              <li>Built with SwiftUI and iOS 26 Liquid Glass</li>
              <li>A <u>rootful</u> jailbreak</li>
            </ul>
          </div>
          <div>
            <h3>What package managers does it come with?</h3>
            <ul>
              <li>Sileo (recommended), Zebra</li>
            </ul>
          </div>
          <div>
            <h3>Is it open source?</h3>
            <ul>
              <li>
                Yes. The source can be found{" "}
                <a
                  href="https://github.com/kilianbalaguer/Obsid1an"
                  target="_blank"
                  rel="noopener noreferrer"
                >
                  here
                </a>
                .
              </li>
            </ul>
          </div>
        </div>
      </section>

      {/* Rootful info */}
      <section className="info-section rootless-section">
        <div>
          <div>
            <h3>What is a rootful jailbreak?</h3>
            <ul>
              <li>
                Rootful jailbreaks provide full read/write access to the entire
                filesystem, including the root partition. This gives you complete
                control over your device.
              </li>
              <li>
                This means tweaks and modifications work the traditional way,
                with no restricted paths or special rootless considerations.
              </li>
            </ul>
          </div>
          <div>
            <h3>How will it affect me as a user?</h3>
            <ul>
              <li>
                Most tweaks that support iOS 27 should work without needing
                rootless-specific builds. You get the full classic jailbreak
                experience.
              </li>
            </ul>
          </div>
        </div>
        <PhoneMockup screenshot="/screenshot_log.png" alt="Obsid1an exploit log" />
      </section>

      {/* Developer info */}
      <section className="developer-section dark-section">
        <div className="developer-info">
          <h3>What exploit does Obsid1an use?</h3>
          <ul>
            <li>
              Obsid1an uses the{" "}
              <a
                href="https://calif.io"
                target="_blank"
                rel="noopener noreferrer"
              >
                calif.io
              </a>{" "}
              kernel exploit, targeting iOS 27.0 and 27.0.1. The exploit
              provides full kernel read/write access for a rootful jailbreak
              environment.
            </li>
          </ul>
        </div>
      </section>

      {/* Credits */}
      <section className="credits-section">
        <h4>Credits</h4>
        <div className="credits-grid">
          <a
            className="credit-box"
            href="https://github.com/kilianbalaguer"
            target="_blank"
            rel="noopener noreferrer"
          >
            {/* eslint-disable-next-line @next/next/no-img-element */}
            <img
              src="https://github.com/kilianbalaguer.png"
              alt="Kilian Balaguer"
              className="credit-avatar"
            />
            <div className="credit-box-desc">
              <h5>Kilian Balaguer</h5>
              <p>Developer</p>
            </div>
          </a>
          <a
            className="credit-box"
            href="https://calif.io"
            target="_blank"
            rel="noopener noreferrer"
          >
            <div className="credit-box-icon">⚡</div>
            <div className="credit-box-desc">
              <h5>calif.io</h5>
              <p>Kernel Exploit</p>
            </div>
          </a>
          <a
            className="credit-box"
            href="https://github.com/Sileo/Sileo"
            target="_blank"
            rel="noopener noreferrer"
          >
            {/* eslint-disable-next-line @next/next/no-img-element */}
            <img
              src="https://github.com/Sileo.png"
              alt="Sileo"
              className="credit-avatar"
            />
            <div className="credit-box-desc">
              <h5>Sileo</h5>
              <p>Package Manager</p>
            </div>
          </a>
          <a
            className="credit-box"
            href="https://github.com/zbrateam/Zebra"
            target="_blank"
            rel="noopener noreferrer"
          >
            {/* eslint-disable-next-line @next/next/no-img-element */}
            <img
              src="https://github.com/zbrateam.png"
              alt="Zebra"
              className="credit-avatar"
            />
            <div className="credit-box-desc">
              <h5>Zebra</h5>
              <p>Package Manager</p>
            </div>
          </a>
        </div>
      </section>

      {/* Footer */}
      <footer className="footer-section">
        <p>Obsid1an — iOS 27 Jailbreak</p>
      </footer>
    </>
  );
}

function PhoneMockup({
  screenshot,
  alt,
}: {
  screenshot: string;
  alt: string;
}) {
  return (
    <div
      className="desktop-only"
      style={{ position: "relative", width: "24rem", flexShrink: 0 }}
    >
      {/* eslint-disable-next-line @next/next/no-img-element */}
      <img
        src="/frame.png"
        alt=""
        style={{
          width: "100%",
          height: "auto",
          display: "block",
          position: "relative",
          zIndex: 2,
          pointerEvents: "none",
        }}
      />
      {/* eslint-disable-next-line @next/next/no-img-element */}
      <img
        src={screenshot}
        alt={alt}
        style={{
          position: "absolute",
          top: "1.8%",
          left: "5.8%",
          width: "88.5%",
          height: "96.3%",
          zIndex: 1,
          objectFit: "cover",
          objectPosition: "top",
          borderRadius: "1.8rem",
        }}
      />
    </div>
  );
}

