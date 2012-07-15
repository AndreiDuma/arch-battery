#include <stdio.h>
#include <string.h>

int get_bat_percent(void);
char *get_bat_status(void);
void get_time(char *);

int main(int argc, char **argv) {
        if (argc != 2) { /* wrong number of arguments */
                printf("battery: usage: \"battery {-p, --percent, -s, --status, -t, --time}\"\n");
        } else if ( (strcmp(argv[1], "-p") == 0) || (strcmp(argv[1], "--percent") == 0) ) { /* PERCENT */
                printf("%d", get_bat_percent());
        } else if ( (strcmp(argv[1], "-s") == 0) || (strcmp(argv[1], "--status") == 0) ) { /* STATUS */
                printf("%s", get_bat_status());
        } else if ( (strcmp(argv[1], "-t") == 0) || (strcmp(argv[1], "--time") == 0) ) { /* TIME */
                char time[10];
                get_time(time); /* puts time left in string time */
                printf("%s", time);
        } else {
                printf("battery: usage: \"battery {-p, --percent, -s, --status, -t, --time}\"\n");
        }

        return 0;
}

int get_bat_percent(void) {
        FILE *fp;
        int charge_now;
        fp = fopen("/sys/class/power_supply/BAT0/charge_now", "r");

        fscanf(fp, "%d", &charge_now);
        fclose(fp);

        int charge_full;
        fp = fopen("/sys/class/power_supply/BAT0/charge_full", "r");

        fscanf(fp, "%d", &charge_full);
        fclose(fp);

        if (charge_now < 0) return 100; /* the Curious case of -1000.. */
        return (charge_now * 100) / charge_full;
}

char *get_bat_status(void) {
        FILE *fp;
        int online;
        fp = fopen("/sys/class/power_supply/ADP1/online", "r");

        fscanf(fp, "%d", &online);
        fclose(fp);

        if (!online) { /* on battery */
                if (get_bat_percent() <= 10) {
                        return "critical";
                } else {
                        return "on battery";
                }
        } else { /* plugged */
                if (get_bat_percent() == 100) {
                        return "full";
                } else {
                        return "charging";
                }
        }
}

void get_time(char *str) {
        FILE *fp;
        int current_draw, charge_now, time;
        fp = fopen("/sys/class/power_supply/BAT0/current_now", "r");

        fscanf(fp, "%d", &current_draw);
        fclose(fp);

        current_draw /= 1000;

        fp = fopen("/sys/class/power_supply/BAT0/charge_now", "r");

        fscanf(fp, "%d", &charge_now);
        fclose(fp);

        time = charge_now / current_draw;
        sprintf(str, "%d", time);
}
