/* File: getStatus.h
 *
 * Author: Jacob Meadows
 *
 * Header file for getStatus.c
 */
#ifndef GETSTATUS_H
#define GETSTATUS_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define POWER_SUPPLY_DIR "/sys/class/power_supply/BAT0/"
#define CURRENT_CHARGE_FILE "charge_now"
#define FULL_CHARGE_FILE "charge_full"
#define DELIMITER " | "
#define POWER_STR "%.2f%%"
#define TIME_STR "%02i:%02i:%02i"
#define DATE_STR "%02i-%02i-%02i"

void fetchStatus(char**, char, bool);
void appendStatus(char**, const char*, bool);
void getFileData(char**, const char*);
float getPower();
void getLongestA(const char*[], size_t, size_t*);

#endif /* GETSTATUS_H */

