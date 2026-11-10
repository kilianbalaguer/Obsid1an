import Image from "next/image";

export default function Home() {
  return (
    <div className="relative min-h-screen overflow-hidden">
      <div
        className="absolute inset-0"
        style={{
          background:
            "linear-gradient(180deg, #7e83ff 0%, #842a8b 60%, #3d1345 100%)",
        }}
      />

      <div className="relative z-10 flex flex-col items-center px-6">
        <nav className="w-full max-w-3xl flex items-center justify-between py-6">
          <span className="text-[15px] font-semibold tracking-tight text-white/90">
            Obsid1an
          </span>
          <div className="flex items-center gap-6">
            <a
              href="https://repo.obsid1an.app"
              className="text-[14px] font-medium text-white/50 hover:text-white/80 transition-colors"
            >
              Repo
            </a>
            <a
              href="https://github.com/kilianbalaguer/Obsid1an"
              target="_blank"
              rel="noopener noreferrer"
              className="text-[14px] font-medium text-white/50 hover:text-white/80 transition-colors"
            >
              GitHub
            </a>
          </div>
        </nav>

        <main className="flex flex-col items-center text-center mt-24 sm:mt-32 max-w-xl">
          <div className="w-[120px] h-[120px] mb-8">
            <Image
              src="/obsid1an.png"
              alt="Obsid1an"
              width={120}
              height={120}
              className="drop-shadow-[0_12px_40px_rgba(0,0,0,0.4)]"
              priority
            />
          </div>

          <h1 className="text-5xl sm:text-6xl font-bold tracking-tight mb-4">
            Obsid1an
          </h1>

          <p className="text-lg text-white/50 mb-3 font-medium">
            Semi-untethered jailbreak for iOS 27
          </p>

          <p className="text-sm text-white/30 mb-12">
            Supports iOS 27.0 — 27.0.1
          </p>

          <div className="flex flex-col sm:flex-row items-center gap-3 w-full max-w-xs">
            <a
              href="https://github.com/kilianbalaguer/Obsid1an/releases"
              target="_blank"
              rel="noopener noreferrer"
              className="w-full sm:w-auto px-8 py-3.5 rounded-full bg-white/90 text-[#1a1a2e] text-[15px] font-semibold text-center hover:bg-white transition-colors"
            >
              Download IPA
            </a>
            <a
              href="https://repo.obsid1an.app"
              className="w-full sm:w-auto px-8 py-3.5 rounded-full bg-white/10 backdrop-blur-md border border-white/10 text-white text-[15px] font-semibold text-center hover:bg-white/15 transition-colors"
            >
              Add Repo
            </a>
          </div>
        </main>

        <section className="mt-32 sm:mt-40 w-full max-w-2xl mb-24">
          <div className="grid grid-cols-1 sm:grid-cols-3 gap-4">
            <Feature
              title="Exploit"
              desc="Kernel read/write via calif.io vulnerability chain."
            />
            <Feature
              title="Tweaks"
              desc="Full tweak injection with ElleKit. Install via Sileo or Zebra."
            />
            <Feature
              title="Respring"
              desc="Instant SpringBoard restart. Safe mode and userspace reboot."
            />
          </div>
        </section>

        <footer className="w-full max-w-3xl py-8 flex items-center justify-between text-[13px] text-white/25">
          <span>Obsid1an</span>
          <a
            href="https://github.com/kilianbalaguer"
            target="_blank"
            rel="noopener noreferrer"
            className="hover:text-white/50 transition-colors"
          >
            Kilian Balaguer
          </a>
        </footer>
      </div>
    </div>
  );
}

function Feature({ title, desc }: { title: string; desc: string }) {
  return (
    <div className="rounded-2xl bg-white/[0.06] backdrop-blur-sm border border-white/[0.06] p-5">
      <h3 className="text-[15px] font-semibold text-white/90 mb-1.5">
        {title}
      </h3>
      <p className="text-[13px] leading-relaxed text-white/40">{desc}</p>
    </div>
  );
}
