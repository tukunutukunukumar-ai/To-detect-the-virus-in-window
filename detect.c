#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void logOutput(const char *content) {
    FILE *f = fopen("DefenderScanLog.txt", "a");
    if (!f) return;

    time_t t = time(NULL);
    fprintf(f, "\n-----------------------\n");
    fprintf(f, "Log Entry: %s", ctime(&t));
    fprintf(f, "%s\n", content);
    fclose(f);
}

void runPowerShell(const char *command) {
    char fullCmd[2048];
    snprintf(fullCmd, sizeof(fullCmd),
             "powershell.exe -Command \"%s\"",
             command);

    printf("\n[Executing]\n%s\n\n", command);
    system(fullCmd);

    logOutput(command);
}

void quickScan() {
    printf("[+] Running Quick Scan...\n");
    runPowerShell("Start-MpScan -ScanType QuickScan");
}

void fullScan() {
    printf("[+] Running Full System Scan...\n");
    runPowerShell("Start-MpScan -ScanType FullScan");
}

void customScan() {
    char path[512];
    printf("Enter folder path to scan: ");
    fgets(path, sizeof(path), stdin);

    // Remove newline
    path[strcspn(path, "\n")] = 0;

    char cmd[1024];
    snprintf(cmd, sizeof(cmd),
             "Start-MpScan -ScanType CustomScan -ScanPath '%s'",
             path);

    printf("[+] Scanning folder: %s\n", path);
    runPowerShell(cmd);
}

void showThreatHistory() {
    printf("[+] Getting Threat History...\n");
    runPowerShell("Get-MpThreatDetection | Format-List *");
}

void showStatus() {
    printf("[+] Displaying Windows Defender Status...\n");
    runPowerShell("Get-MpComputerStatus | Format-List *");
}

void menu() {
    printf("===============================================\n");
    printf(" WINDOWS DEFENDER VIRUS SCANNER (SAFE)\n");
    printf("===============================================\n\n");

    printf("1. Quick Scan\n");
    printf("2. Full Scan\n");
    printf("3. Custom Folder Scan\n");
    printf("4. Show Threat History\n");
    printf("5. Show Defender Status\n");
    printf("6. Exit\n");
    printf("\nOption: ");
}

int main() {
    while (1) {
        clearScreen();
        menu();

        char choice[10];
        fgets(choice, sizeof(choice), stdin);

        switch (choice[0]) {
            case '1':
                clearScreen();
                quickScan();
                break;

            case '2':
                clearScreen();
                fullScan();
                break;

            case '3':
                clearScreen();
                customScan();
                break;

            case '4':
                clearScreen();
                showThreatHistory();
                break;

            case '5':
                clearScreen();
                showStatus();
                break;

            case '6':
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }

        printf("\nPress ENTER to continue...");
        getchar();
    }

    return 0;
}
