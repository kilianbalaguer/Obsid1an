/*
 * ShardFetch — system info for jailbroken iOS
 * Rainbow Apple logo + device/OS/jailbreak info
 * Supports rootful, rootless, and roothide environments
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/sysctl.h>
#include <sys/utsname.h>
#include <sys/statvfs.h>
#include <sys/types.h>
#include <mach/mach.h>
#include <mach/mach_host.h>
#include <time.h>
#include <pwd.h>
#include <dirent.h>

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>

#ifndef kIOMainPortDefault
#define kIOMainPortDefault 0
#endif

/* ── ANSI colors ─────────────────────────────────────────── */

#define C_RESET   "\033[0m"
#define C_BOLD    "\033[1m"
#define C_DIM     "\033[2m"
#define C_GREEN   "\033[32m"
#define C_YELLOW  "\033[33m"
#define C_ORANGE  "\033[38;5;208m"
#define C_RED     "\033[31m"
#define C_PURPLE  "\033[35m"
#define C_BLUE    "\033[34m"
#define C_CYAN    "\033[36m"
#define C_WHITE   "\033[37m"

/* ── Rainbow Apple ASCII art (17 lines) ──────────────────── */

#define LOGO_LINES 17
#define LOGO_WIDTH 36

static const char *logo_art[] = {
    "                 'c.          ",
    "              ,xNMM.          ",
    "            .OMMMMo           ",
    "            OMMM0,            ",
    "  .;loddo:' loolloddol;.     ",
    "cKMMMMMMMMMMNWMMMMMMMMMM0:   ",
    ".KMMMMMMMMMMMMMMMMMMMMMMMWd. ",
    " XMMMMMMMMMMMMMMMMMMMMMMMX. ",
    ";MMMMMMMMMMMMMMMMMMMMMMMM:   ",
    ":MMMMMMMMMMMMMMMMMMMMMMMM:   ",
    ".MMMMMMMMMMMMMMMMMMMMMMMMX.  ",
    " kMMMMMMMMMMMMMMMMMMMMMMMMWd ",
    " .XMMMMMMMMMMMMMMMMMMMMMMMMk ",
    "  .XMMMMMMMMMMMMMMMMMMMMMMK. ",
    "    kMMMMMMMMMMMMMMMMMMMMd    ",
    "     ;KMMMMMMMWXXWMMMMMk.    ",
    "       .cooc,.    .,coo:.    "
};

static const char *logo_colors[] = {
    C_GREEN,  C_GREEN,  C_GREEN,
    C_YELLOW, C_YELLOW, C_YELLOW,
    C_ORANGE, C_ORANGE, C_ORANGE,
    C_RED,    C_RED,
    C_PURPLE, C_PURPLE, C_PURPLE,
    C_BLUE,   C_BLUE,   C_BLUE
};

/* ── Device model table ──────────────────────────────────── */

typedef struct { const char *id; const char *name; const char *chip; } device_t;

static const device_t devices[] = {
    /* iPhone */
    {"iPhone6,1", "iPhone 5s", "A7"},
    {"iPhone6,2", "iPhone 5s", "A7"},
    {"iPhone7,1", "iPhone 6 Plus", "A8"},
    {"iPhone7,2", "iPhone 6", "A8"},
    {"iPhone8,1", "iPhone 6s", "A9"},
    {"iPhone8,2", "iPhone 6s Plus", "A9"},
    {"iPhone8,4", "iPhone SE", "A9"},
    {"iPhone9,1", "iPhone 7", "A10 Fusion"},
    {"iPhone9,2", "iPhone 7 Plus", "A10 Fusion"},
    {"iPhone9,3", "iPhone 7", "A10 Fusion"},
    {"iPhone9,4", "iPhone 7 Plus", "A10 Fusion"},
    {"iPhone10,1", "iPhone 8", "A11 Bionic"},
    {"iPhone10,2", "iPhone 8 Plus", "A11 Bionic"},
    {"iPhone10,3", "iPhone X", "A11 Bionic"},
    {"iPhone10,4", "iPhone 8", "A11 Bionic"},
    {"iPhone10,5", "iPhone 8 Plus", "A11 Bionic"},
    {"iPhone10,6", "iPhone X", "A11 Bionic"},
    {"iPhone11,2", "iPhone XS", "A12 Bionic"},
    {"iPhone11,4", "iPhone XS Max", "A12 Bionic"},
    {"iPhone11,6", "iPhone XS Max", "A12 Bionic"},
    {"iPhone11,8", "iPhone XR", "A12 Bionic"},
    {"iPhone12,1", "iPhone 11", "A13 Bionic"},
    {"iPhone12,3", "iPhone 11 Pro", "A13 Bionic"},
    {"iPhone12,5", "iPhone 11 Pro Max", "A13 Bionic"},
    {"iPhone12,8", "iPhone SE 2", "A13 Bionic"},
    {"iPhone13,1", "iPhone 12 mini", "A14 Bionic"},
    {"iPhone13,2", "iPhone 12", "A14 Bionic"},
    {"iPhone13,3", "iPhone 12 Pro", "A14 Bionic"},
    {"iPhone13,4", "iPhone 12 Pro Max", "A14 Bionic"},
    {"iPhone14,2", "iPhone 13 Pro", "A15 Bionic"},
    {"iPhone14,3", "iPhone 13 Pro Max", "A15 Bionic"},
    {"iPhone14,4", "iPhone 13 mini", "A15 Bionic"},
    {"iPhone14,5", "iPhone 13", "A15 Bionic"},
    {"iPhone14,6", "iPhone SE 3", "A15 Bionic"},
    {"iPhone14,7", "iPhone 14", "A15 Bionic"},
    {"iPhone14,8", "iPhone 14 Plus", "A15 Bionic"},
    {"iPhone15,2", "iPhone 14 Pro", "A16 Bionic"},
    {"iPhone15,3", "iPhone 14 Pro Max", "A16 Bionic"},
    {"iPhone15,4", "iPhone 15", "A16 Bionic"},
    {"iPhone15,5", "iPhone 15 Plus", "A16 Bionic"},
    {"iPhone16,1", "iPhone 15 Pro", "A17 Pro"},
    {"iPhone16,2", "iPhone 15 Pro Max", "A17 Pro"},
    {"iPhone17,1", "iPhone 16 Pro", "A18 Pro"},
    {"iPhone17,2", "iPhone 16 Pro Max", "A18 Pro"},
    {"iPhone17,3", "iPhone 16", "A18"},
    {"iPhone17,4", "iPhone 16 Plus", "A18"},
    {"iPhone17,5", "iPhone 16e", "A18"},
    /* iPad */
    {"iPad5,1", "iPad mini 4", "A8"},
    {"iPad5,2", "iPad mini 4", "A8"},
    {"iPad6,3", "iPad Pro 9.7\"", "A9X"},
    {"iPad6,4", "iPad Pro 9.7\"", "A9X"},
    {"iPad6,7", "iPad Pro 12.9\"", "A9X"},
    {"iPad6,8", "iPad Pro 12.9\"", "A9X"},
    {"iPad6,11", "iPad 5", "A9"},
    {"iPad6,12", "iPad 5", "A9"},
    {"iPad7,1", "iPad Pro 12.9\" 2", "A10X Fusion"},
    {"iPad7,2", "iPad Pro 12.9\" 2", "A10X Fusion"},
    {"iPad7,3", "iPad Pro 10.5\"", "A10X Fusion"},
    {"iPad7,4", "iPad Pro 10.5\"", "A10X Fusion"},
    {"iPad7,5", "iPad 6", "A10 Fusion"},
    {"iPad7,6", "iPad 6", "A10 Fusion"},
    {"iPad7,11", "iPad 7", "A10 Fusion"},
    {"iPad7,12", "iPad 7", "A10 Fusion"},
    {"iPad8,1", "iPad Pro 11\"", "A12X Bionic"},
    {"iPad8,2", "iPad Pro 11\"", "A12X Bionic"},
    {"iPad8,3", "iPad Pro 11\"", "A12X Bionic"},
    {"iPad8,4", "iPad Pro 11\"", "A12X Bionic"},
    {"iPad11,1", "iPad mini 5", "A12 Bionic"},
    {"iPad11,2", "iPad mini 5", "A12 Bionic"},
    {"iPad11,3", "iPad Air 3", "A12 Bionic"},
    {"iPad11,4", "iPad Air 3", "A12 Bionic"},
    {"iPad11,6", "iPad 8", "A12 Bionic"},
    {"iPad11,7", "iPad 8", "A12 Bionic"},
    {"iPad12,1", "iPad 9", "A13 Bionic"},
    {"iPad12,2", "iPad 9", "A13 Bionic"},
    {"iPad13,1", "iPad Air 4", "A14 Bionic"},
    {"iPad13,2", "iPad Air 4", "A14 Bionic"},
    {"iPad13,4", "iPad Pro 11\" 3", "M1"},
    {"iPad13,5", "iPad Pro 11\" 3", "M1"},
    {"iPad13,8", "iPad Pro 12.9\" 5", "M1"},
    {"iPad13,9", "iPad Pro 12.9\" 5", "M1"},
    {"iPad13,16", "iPad Air 5", "M1"},
    {"iPad13,17", "iPad Air 5", "M1"},
    {"iPad13,18", "iPad 10", "A14 Bionic"},
    {"iPad13,19", "iPad 10", "A14 Bionic"},
    {"iPad14,1", "iPad mini 6", "A15 Bionic"},
    {"iPad14,2", "iPad mini 6", "A15 Bionic"},
    {"iPad14,3", "iPad Pro 11\" 4", "M2"},
    {"iPad14,4", "iPad Pro 11\" 4", "M2"},
    {"iPad14,5", "iPad Pro 12.9\" 6", "M2"},
    {"iPad14,6", "iPad Pro 12.9\" 6", "M2"},
    {"iPad14,8", "iPad Air 6 11\"", "M2"},
    {"iPad14,9", "iPad Air 6 11\"", "M2"},
    {"iPad14,10", "iPad Air 6 13\"", "M2"},
    {"iPad14,11", "iPad Air 6 13\"", "M2"},
    {"iPad16,1", "iPad mini 7", "A17 Pro"},
    {"iPad16,2", "iPad mini 7", "A17 Pro"},
    {"iPad16,3", "iPad Pro 11\" 5", "M4"},
    {"iPad16,4", "iPad Pro 11\" 5", "M4"},
    {"iPad16,5", "iPad Pro 13\" 5", "M4"},
    {"iPad16,6", "iPad Pro 13\" 5", "M4"},
    /* iPod */
    {"iPod7,1", "iPod touch 6", "A8"},
    {"iPod9,1", "iPod touch 7", "A10 Fusion"},
    {NULL, NULL, NULL}
};

/* ── System info helpers ─────────────────────────────────── */

static int sysctl_string(const char *name, char *buf, size_t len) {
    size_t sz = len;
    if (sysctlbyname(name, buf, &sz, NULL, 0) == 0) {
        buf[sz < len ? sz : len - 1] = '\0';
        return 0;
    }
    buf[0] = '\0';
    return -1;
}

static void get_username(char *buf, size_t len) {
    struct passwd *pw = getpwuid(getuid());
    if (pw && pw->pw_name)
        snprintf(buf, len, "%s", pw->pw_name);
    else {
        const char *u = getenv("USER");
        snprintf(buf, len, "%s", u ? u : "user");
    }
}

static void get_hostname(char *buf, size_t len) {
    gethostname(buf, len);
    buf[len - 1] = '\0';
    char *dot = strchr(buf, '.');
    if (dot) *dot = '\0';
}

static void get_os_version(char *buf, size_t len) {
    char ver[64] = {0};
    if (sysctl_string("kern.osproductversion", ver, sizeof(ver)) == 0) {
        snprintf(buf, len, "iOS %s", ver);
        return;
    }
    /* fallback: read SystemVersion.plist */
    FILE *f = fopen("/System/Library/CoreServices/SystemVersion.plist", "r");
    if (f) {
        char line[256];
        int found_key = 0;
        while (fgets(line, sizeof(line), f)) {
            if (strstr(line, "<key>ProductVersion</key>"))
                found_key = 1;
            else if (found_key) {
                char *start = strstr(line, "<string>");
                char *end = strstr(line, "</string>");
                if (start && end) {
                    start += 8;
                    *end = '\0';
                    snprintf(buf, len, "iOS %s", start);
                    fclose(f);
                    return;
                }
                found_key = 0;
            }
        }
        fclose(f);
    }
    struct utsname u;
    if (uname(&u) == 0)
        snprintf(buf, len, "Darwin %s", u.release);
    else
        snprintf(buf, len, "iOS (unknown)");
}

static void get_device(char *name_buf, size_t nlen, char *chip_buf, size_t clen) {
    char machine[64] = {0};
    sysctl_string("hw.machine", machine, sizeof(machine));

    for (const device_t *d = devices; d->id; d++) {
        if (strcmp(machine, d->id) == 0) {
            snprintf(name_buf, nlen, "%s", d->name);
            snprintf(chip_buf, clen, "%s", d->chip);
            return;
        }
    }
    snprintf(name_buf, nlen, "%s", machine);
    snprintf(chip_buf, clen, "%s", machine);
}

static const char *detect_jailbreak_type(void) {
    /* roothide: check for .jbroot paths */
    DIR *dir = opendir("/var/containers/Bundle");
    if (dir) {
        struct dirent *ent;
        while ((ent = readdir(dir))) {
            if (strncmp(ent->d_name, ".jbroot-", 8) == 0) {
                closedir(dir);
                return "roothide";
            }
        }
        closedir(dir);
    }
    /* rootless: /var/jb exists */
    if (access("/var/jb", F_OK) == 0)
        return "rootless";
    /* rootful: default on jailbroken device */
    return "rootful";
}

static void get_jailbreak(char *buf, size_t len) {
    const char *type = detect_jailbreak_type();

    struct { const char *path; const char *name; } checks[] = {
        {"/var/mobile/Library/.obsid1an",        "Obsid1an"},
        {"/var/jb/.installed_dopamine",          "Dopamine"},
        {"/var/jb/.installed_palera1n",          "palera1n"},
        {"/.installed_unc0ver",                  "unc0ver"},
        {"/var/jb/.installed_xina15",            "XinaA15"},
        {"/.installed_taurine",                  "Taurine"},
        {"/.bootstrapped",                       "checkra1n"},
        {"/var/LIY/.installed_trollstore",       "TrollStore"},
        {"/Applications/Cydia.app",              "Cydia (unknown)"},
        {NULL, NULL}
    };

    for (int i = 0; checks[i].path; i++) {
        if (access(checks[i].path, F_OK) == 0) {
            snprintf(buf, len, "%s (%s)", checks[i].name, type);
            return;
        }
    }
    if (getuid() == 0)
        snprintf(buf, len, "Unknown (%s)", type);
    else
        snprintf(buf, len, "None detected");
}

static void get_uptime(char *buf, size_t len) {
    struct timeval boottime;
    size_t sz = sizeof(boottime);
    int mib[2] = { CTL_KERN, KERN_BOOTTIME };
    if (sysctl(mib, 2, &boottime, &sz, NULL, 0) != 0) {
        snprintf(buf, len, "unknown");
        return;
    }
    time_t now = time(NULL);
    long secs = now - boottime.tv_sec;
    int days  = (int)(secs / 86400);
    int hours = (int)((secs % 86400) / 3600);
    int mins  = (int)((secs % 3600) / 60);

    if (days > 0)
        snprintf(buf, len, "%d day%s, %d hour%s", days, days == 1 ? "" : "s", hours, hours == 1 ? "" : "s");
    else if (hours > 0)
        snprintf(buf, len, "%d hour%s, %d min%s", hours, hours == 1 ? "" : "s", mins, mins == 1 ? "" : "s");
    else
        snprintf(buf, len, "%d min%s", mins, mins == 1 ? "" : "s");
}

static void get_memory(char *buf, size_t len) {
    mach_port_t host = mach_host_self();
    vm_size_t page_size;
    host_page_size(host, &page_size);

    vm_statistics64_data_t vm;
    mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;
    if (host_statistics64(host, HOST_VM_INFO64, (host_info64_t)&vm, &count) != KERN_SUCCESS) {
        snprintf(buf, len, "unknown");
        return;
    }

    uint64_t total;
    size_t sz = sizeof(total);
    sysctlbyname("hw.memsize", &total, &sz, NULL, 0);

    uint64_t used = ((uint64_t)vm.active_count + vm.wire_count) * page_size;
    double used_gb  = (double)used  / (1024.0 * 1024.0 * 1024.0);
    double total_gb = (double)total / (1024.0 * 1024.0 * 1024.0);
    snprintf(buf, len, "%.1f GiB / %.1f GiB", used_gb, total_gb);
}

static void get_disk(char *buf, size_t len) {
    struct statvfs st;
    if (statvfs("/", &st) != 0) {
        snprintf(buf, len, "unknown");
        return;
    }
    double total = (double)st.f_blocks * st.f_frsize / (1024.0 * 1024.0 * 1024.0);
    double avail = (double)st.f_bavail * st.f_frsize / (1024.0 * 1024.0 * 1024.0);
    double used  = total - avail;
    snprintf(buf, len, "%.1f GiB / %.1f GiB", used, total);
}

static void get_battery(char *buf, size_t len) {
    CFMutableDictionaryRef match = IOServiceMatching("IOPMPowerSource");
    if (!match) { snprintf(buf, len, "N/A"); return; }

    io_service_t svc = IOServiceGetMatchingService(kIOMainPortDefault, match);
    if (!svc) { snprintf(buf, len, "N/A"); return; }

    int level = -1, charging = 0;
    CFNumberRef cap = IORegistryEntryCreateCFProperty(svc, CFSTR("CurrentCapacity"), kCFAllocatorDefault, 0);
    CFBooleanRef chg = IORegistryEntryCreateCFProperty(svc, CFSTR("IsCharging"), kCFAllocatorDefault, 0);

    if (cap) { CFNumberGetValue(cap, kCFNumberIntType, &level); CFRelease(cap); }
    if (chg) { charging = CFBooleanGetValue(chg); CFRelease(chg); }
    IOObjectRelease(svc);

    if (level >= 0)
        snprintf(buf, len, "%d%% (%s)", level, charging ? "charging" : "discharging");
    else
        snprintf(buf, len, "N/A");
}

static void get_shell(char *buf, size_t len) {
    const char *shell = getenv("SHELL");
    if (shell) {
        const char *name = strrchr(shell, '/');
        snprintf(buf, len, "%s", name ? name + 1 : shell);
    } else {
        snprintf(buf, len, "unknown");
    }
}

static void get_terminal(char *buf, size_t len) {
    const char *term = getenv("TERM_PROGRAM");
    if (!term) term = getenv("TERM");
    snprintf(buf, len, "%s", term ? term : "unknown");
}

static int get_cpu_cores(void) {
    int cores = 0;
    size_t sz = sizeof(cores);
    sysctlbyname("hw.ncpu", &cores, &sz, NULL, 0);
    return cores;
}

/* ── Output ──────────────────────────────────────────────── */

#define MAX_INFO 20

int main(void) {
    char username[64], hostname[128], os[64], device[64], chip[64];
    char jailbreak[128], uptime[128], memory[64], disk[64];
    char battery[64], shell[32], terminal[64];

    get_username(username, sizeof(username));
    get_hostname(hostname, sizeof(hostname));
    get_os_version(os, sizeof(os));
    get_device(device, sizeof(device), chip, sizeof(chip));
    get_jailbreak(jailbreak, sizeof(jailbreak));
    get_uptime(uptime, sizeof(uptime));
    get_memory(memory, sizeof(memory));
    get_disk(disk, sizeof(disk));
    get_battery(battery, sizeof(battery));
    get_shell(shell, sizeof(shell));
    get_terminal(terminal, sizeof(terminal));
    int cores = get_cpu_cores();

    /* build info lines */
    char info[MAX_INFO][256];
    int n = 0;

    snprintf(info[n++], 256, "%s%s%s@%s%s%s", C_BOLD, username, C_RESET, C_BOLD, hostname, C_RESET);

    /* separator — match length of user@host */
    {
        int slen = (int)(strlen(username) + 1 + strlen(hostname));
        char sep[128];
        if (slen > 126) slen = 126;
        memset(sep, '-', slen);
        sep[slen] = '\0';
        snprintf(info[n++], 256, "%s%s%s", C_DIM, sep, C_RESET);
    }

    snprintf(info[n++], 256, "%sOS%s:        %s", C_BOLD, C_RESET, os);
    snprintf(info[n++], 256, "%sDevice%s:    %s", C_BOLD, C_RESET, device);
    snprintf(info[n++], 256, "%sJailbreak%s: %s", C_BOLD, C_RESET, jailbreak);
    snprintf(info[n++], 256, "%sUptime%s:    %s", C_BOLD, C_RESET, uptime);
    snprintf(info[n++], 256, "%sCPU%s:       %s (%d cores)", C_BOLD, C_RESET, chip, cores);
    snprintf(info[n++], 256, "%sMemory%s:    %s", C_BOLD, C_RESET, memory);
    snprintf(info[n++], 256, "%sStorage%s:   %s", C_BOLD, C_RESET, disk);
    snprintf(info[n++], 256, "%sBattery%s:   %s", C_BOLD, C_RESET, battery);
    snprintf(info[n++], 256, "%sShell%s:     %s", C_BOLD, C_RESET, shell);
    snprintf(info[n++], 256, "%sTerminal%s:  %s", C_BOLD, C_RESET, terminal);

    /* blank line before color palette */
    info[n][0] = '\0'; n++;

    /* color palette blocks */
    snprintf(info[n++], 256,
        "\033[40m   \033[41m   \033[42m   \033[43m   "
        "\033[44m   \033[45m   \033[46m   \033[47m   " C_RESET);

    /* print logo + info side by side */
    int total = LOGO_LINES > n ? LOGO_LINES : n;
    printf("\n");
    for (int i = 0; i < total; i++) {
        if (i < LOGO_LINES)
            printf("  %s%s%s", logo_colors[i], logo_art[i], C_RESET);
        else
            printf("  %*s", LOGO_WIDTH, "");

        if (i < n)
            printf("  %s", info[i]);

        printf("\n");
    }
    printf("\n");

    return 0;
}
