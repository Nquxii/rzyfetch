#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <string.h>
#include <sys/utsname.h>

int main() {
    /* Declares */
    struct sysinfo si;
    sysinfo (&si);

    struct utsname un;
    uname (&un);

    int64_t total_ram, uptime, processes;

    double megabyte = 1024 * 1024;
    double ramMB, availableRAM, percentageUsed;

    /* Colors */
    char cr[10]= "\033[1;36m";
    char cl[10] = "\033[0m";

    /* Relevant user environment variables */
    char *user = getenv("USER");
    char *terminal = getenv("TERM");
    char *shell = getenv("SHELL");
    char *lang = getenv("LANG");

    // Hostname
    char hostname[_SC_HOST_NAME_MAX + 1];
    gethostname(hostname, _SC_HOST_NAME_MAX + 1);

    // Uptime
    uptime = (float)si.uptime / 60;

    // Total ram
    total_ram = si.totalram *(unsigned long long)si.mem_unit / 1024;

    // Read memory using free -m
    FILE *fp; char path[1035];

    fp = popen("free -m | awk '{print $3}'", "r");

    fgets(path, sizeof(path), fp);

    char mem[100];
    fscanf(fp, "%s", mem);

    // find ram in megabytes
    ramMB = si.totalram/megabyte;

    availableRAM = atof(mem);
    percentageUsed = availableRAM/ramMB * 100;

    /* Output */
    printf("%s~ user     -->%s  %s@%s\n", cr, cl, user, hostname);
    printf("%s~ release  -->%s  %s %s\n", cr, cl, un.release, un.machine);
    printf("%s~ terminal -->%s  %s\n", cr, cl, terminal);
    printf("%s~ shell    -->%s  %s\n", cr, cl, shell);
    printf("%s~ memory   -->%s  %s/%.0f - %.0f%%\n", cr, cl, mem, ramMB, percentageUsed);
    printf("%s~ uptime   -->%s  %li minutes \n", cr, cl, uptime);
    printf("%s~ locale   -->%s  %s\n", cr, cl, lang);
    printf("%s~ procs    -->%s  %d\n", cr, cl, si.procs);

    return 0;
}

