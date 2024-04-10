/* File: getStatus.c
 *
 * Author: Jacob Meadows
 *
 * Calculates or fetches the requested status information.
 */
#include "getStatus.h"

int main(int argc, char** argv)
{
    char* result;
    bool first_item = true;
    char request;
    for (int i = 1; i < argc; ++i) {
	int j = 0;
	while (request = argv[i][++j]) {
	    fetchStatus(&result, request, first_item);
	    if (first_item) {
		first_item = false;
	    }
	}
    }

    if (!first_item) {
	printf("%s", result);
	free(result);
    }

    return 0;
}

void fetchStatus(char** result, char request, bool first_item) {
    switch (request) {
	case 'p':
	    float power = getPower();
	    appendStatus(result, POWER_STR, first_item);
	    asprintf(result, *result, power);
	    break;
	case 't':
	    // variables defined below are also used in case 'd'
	    time_t rawtime;
	    struct tm* timeinfo;

	    time(&rawtime);
	    timeinfo = localtime(&rawtime);
	    appendStatus(result, TIME_STR, first_item);
	    asprintf(result, *result,
		     timeinfo->tm_hour,
		     timeinfo->tm_min,
		     timeinfo->tm_sec);
	    break;
	case 'd':
	    time(&rawtime);
	    timeinfo = localtime(&rawtime);
	    appendStatus(result, DATE_STR, first_item);
	    asprintf(result, *result,
		     timeinfo->tm_year + 1900,
		     timeinfo->tm_mon + 1,
		     timeinfo->tm_mday);
	    break;
    }
}

void appendStatus(char** status, const char* format, bool first_item) {
    if (!first_item) {
	asprintf(status, "%s%s%s", *status, DELIMITER, format);
    }
    else {
	asprintf(status, "%s", format);
    }
}


float getPower() {
    const size_t powerSupplyDirLength = strlen(POWER_SUPPLY_DIR);

    const char* BATTERY_FILES[] = { CURRENT_CHARGE_FILE, FULL_CHARGE_FILE };
    const size_t fileCount = sizeof(BATTERY_FILES) / sizeof(const char*);

    float result;

    char* currentCharge;
    char* fullCharge;

    size_t maxFileLength;
    getLongestA(BATTERY_FILES, fileCount, &maxFileLength);

    char fileDir[powerSupplyDirLength + maxFileLength + 1];
    strncpy(fileDir, POWER_SUPPLY_DIR, powerSupplyDirLength);
    // get current charge of battery
    strcpy(fileDir + powerSupplyDirLength, CURRENT_CHARGE_FILE);
    getFileData(&currentCharge, fileDir);
    // get maximum possible charge of battery
    strcpy(fileDir + powerSupplyDirLength, FULL_CHARGE_FILE);
    getFileData(&fullCharge, fileDir);
    // output percent of charge left in battery with 2 decimal
    result = 100 * atof(currentCharge) / atof(fullCharge);
    free(currentCharge);
    free(fullCharge);

    return result;
}

void getLongestA(const char* data[], size_t size, size_t* result) {
    *result = 0;

    size_t length;
    for (size_t i = 0; i < size; ++i) {
	if ((length = strlen(data[i])) > *result)
	    *result = length;
    }
}

void getFileData(char** result, const char* fileName)
{
    FILE* file = fopen(fileName, "r");
    *result = (char*) malloc(8 * sizeof(char));
    fgets(*result, 8, file);
    fclose(file);
}

