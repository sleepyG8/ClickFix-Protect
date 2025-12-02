#include <Windows.h>
#include <stdio.h>

// Got this original clipboard idea from https://cocomelonc.github.io/malware/2025/05/10/malware-tricks-47.html shout out to cocomelon 

BOOL samedata = FALSE;
char *LastData = NULL;

typedef struct {
    char data[256];
    int size;
} hits;

DWORD WINAPI clickFixProtect(LPVOID lpParam) {

    hits* hit = malloc(sizeof(hits));
    
    while (1) {

    if (OpenClipboard(NULL)) {

        if (IsClipboardFormatAvailable(CF_TEXT)) {

        HANDLE hData = GetClipboardData(CF_TEXT);
  
        if (hData == NULL) {
            printf("error\n");
            CloseClipboard();
             return FALSE;
            }
  
            unsigned char *clipData = (char*)GlobalLock(hData);
    
            if (LastData == NULL || strcmp(LastData, clipData) != 0) {
                samedata = FALSE;
             } else {
               samedata = TRUE;
            }


            if (clipData != NULL && !samedata) {

                LastData = strdup((char*)clipData);
                GlobalUnlock(hData);
                
                FILE* f = fopen("clickCheck.txt", "rb");

                char line[256];
                while (fgets(line, sizeof(line), f)) {
                
                line[strcspn(line, "\r\n")] = '\0';
                
                strcpy(hit->data, line);
                hit->size = sizeof(line);

                if (strcmp(clipData, hit->data) == 0) {
                    printf("Found a malicous clickFix!\n");
                    printf("%s\n", line);
                }

                }

                fclose(f);
                CloseClipboard();  
            } else {
                LastData = strdup(clipData);
                CloseClipboard();
                GlobalUnlock(hData);;
            }

            Sleep(300);

}
}
}
return TRUE;
}

int main() {

HANDLE hThread = CreateThread(NULL, 0, clickFixProtect, NULL, 0, 0);

WaitForSingleObject(hThread, INFINITE);


return 0;


}
