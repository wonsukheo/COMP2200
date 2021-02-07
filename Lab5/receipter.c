#include <stdio.h>
#include <time.h>
#include <string.h>
#include "receipter.h"

#define RECEIPT_WIDTH (51)

static char s_heading_buffer[256];
static char* s_heading_buffer_ptr = s_heading_buffer;
static char s_item_buffer[512];
static char* s_item_buffer_ptr = s_item_buffer;
static char s_tip_buffer[64];
static char* s_tip_buffer_ptr = s_tip_buffer;
static char s_total_buffer[512];
static char* s_total_buffer_ptr = s_total_buffer;
static char s_message_buffer[128];
static char* s_message_buffer_ptr = s_message_buffer;
static char s_ending_buffer[128];
static char* s_ending_buffer_ptr = s_ending_buffer;

static size_t s_item_count = 0u;
static double s_subtotal = 0.00;
static size_t s_order_number = 0u;
static double s_tip = 0.00;
static char s_spacing[51];

int add_item(const char* name, double price)
{ 
    int printed_item = 0;
    
    if (s_item_count >= 10) {
        return FALSE;
    }

    printed_item = sprintf(s_item_buffer_ptr, "%33.25s %16.2f\n", name, price);

    if (printed_item < 0) {
        return FALSE;
    } else {
        s_item_count++;
        s_subtotal += price;
        s_item_buffer_ptr += RECEIPT_WIDTH;
        
        return TRUE;
    }
}

void set_tip(double tip)
{
    sprintf(s_tip_buffer_ptr, "%33s %16.2f\n", "Tip", tip);
    s_tip = tip;
}

void set_total(void)
{
    double tax = (s_subtotal * .05) + 0.005;

    sprintf(s_total_buffer_ptr, "%s", "\n");
    s_total_buffer_ptr++;
    sprintf(s_total_buffer_ptr, "%33s %16.2f\n", "Subtotal", s_subtotal);
    s_total_buffer_ptr += RECEIPT_WIDTH;

    if (s_tip != 0.00) {    
        sprintf(s_total_buffer_ptr, "%50s\n", s_tip_buffer);
        s_total_buffer_ptr += RECEIPT_WIDTH;
    }

    sprintf(s_total_buffer_ptr, "%33s %16.2f\n", "Tax", tax);
    s_total_buffer_ptr += RECEIPT_WIDTH;
    sprintf(s_total_buffer_ptr, "%33s %16.2f\n", "Total", s_subtotal + tax + s_tip);
    s_total_buffer_ptr += RECEIPT_WIDTH;
    sprintf(s_total_buffer_ptr, "%s", "\n");
    s_total_buffer_ptr++;
}

void set_message(const char* message)
{
    if (strlen(message) >= 75) {
        sprintf(s_message_buffer_ptr, "%.50s\n", message);
        s_message_buffer_ptr += RECEIPT_WIDTH;
    
        sprintf(s_message_buffer_ptr, "%-.25s\n", message + RECEIPT_WIDTH - 1);
        s_message_buffer_ptr += 26;
    } else if (strlen(message) > RECEIPT_WIDTH - 1 && strlen(message) < 75) {
        sprintf(s_message_buffer_ptr, "%.50s\n", message);
        s_message_buffer_ptr += RECEIPT_WIDTH;
        
        sprintf(s_message_buffer_ptr, "%-.25s\n", message + RECEIPT_WIDTH - 1);
        s_message_buffer_ptr += strlen(message) - 49;
    } else {
        sprintf(s_message_buffer_ptr, "%-s\n", message);
        s_message_buffer_ptr += strlen(message) + 1;
    }
}

void set_ending(void)
{    
    size_t i;

    for (i = 0; i < RECEIPT_WIDTH - 1; ++i) {
        s_spacing[i] = '=';
    }
    s_spacing[i] = '\0';

    sprintf(s_ending_buffer_ptr, "%50s\n", s_spacing);
    s_ending_buffer_ptr += RECEIPT_WIDTH;
    sprintf(s_ending_buffer_ptr, "%50s", "Tax#-51234");
    s_ending_buffer_ptr += RECEIPT_WIDTH - 1;
}

void set_heading(time_t timestamp)
{
    size_t i;
    char time_string[48];
    int hours;
    int minutes;
    int seconds;
    int day;
    int month;
    int year;
    char name_restaurant[] = "Charles' Seafood";

    struct tm* gm = gmtime(&timestamp);

    hours = gm -> tm_hour;
    minutes = gm -> tm_min;
    seconds = gm -> tm_sec;

    day = gm -> tm_mday;
    month = gm -> tm_mon + 1;
    year = gm -> tm_year + 1900;

    sprintf(time_string, "%d-%02d-%02d %02d:%02d:%02d", year, month, day, hours, minutes, seconds);

    for (i = 0; i < RECEIPT_WIDTH - 1; ++i) {
        s_spacing[i] = '-';
    }
    s_spacing[i] = '\0';
    
    sprintf(s_heading_buffer_ptr, "%-s\n", name_restaurant);
    s_heading_buffer_ptr += strlen(name_restaurant) + 1;
    sprintf(s_heading_buffer_ptr, "%50s\n", s_spacing);
    s_heading_buffer_ptr += RECEIPT_WIDTH;
    sprintf(s_heading_buffer_ptr, "%-44s %05d\n", time_string, order_number);
    s_heading_buffer_ptr += RECEIPT_WIDTH;
    sprintf(s_heading_buffer_ptr, "%50s\n", s_spacing);
    s_heading_buffer_ptr += RECEIPT_WIDTH;
}

void reset_receipt(void)
{
    s_item_count = 0u;
    s_subtotal = 0.00;
    s_tip = 0.00;

    s_heading_buffer_ptr = s_heading_buffer;
    s_item_buffer_ptr = s_item_buffer;
    s_total_buffer_ptr = s_total_buffer;
    s_message_buffer_ptr = s_message_buffer;
    *s_message_buffer_ptr = '0';
    s_ending_buffer_ptr = s_ending_buffer;
    s_tip_buffer_ptr = s_tip_buffer;
}
int print_receipt(const char* filename, time_t timestamp)
{
    FILE* stream;

    set_heading(timestamp);
    set_total();
    set_ending();
    
    if (s_item_buffer == s_item_buffer_ptr) {
        reset_receipt();
        return 0;
    } 
    
    stream = fopen(filename, "w+");  
    fwrite(s_heading_buffer, sizeof(s_heading_buffer[0]), s_heading_buffer_ptr - s_heading_buffer, stream);
    fwrite(s_item_buffer, sizeof(s_item_buffer[0]), s_item_buffer_ptr - s_item_buffer, stream);
    fwrite(s_total_buffer, sizeof(s_total_buffer[0]), s_total_buffer_ptr - s_total_buffer, stream);
    fwrite(s_message_buffer, sizeof(s_message_buffer[0]), s_message_buffer_ptr - s_message_buffer, stream);
    fwrite(s_ending_buffer, sizeof(s_ending_buffer[0]), s_ending_buffer_ptr - s_ending_buffer, stream);
    fflush(stream);
    fclose(stream);

    order_number++;
    reset_receipt();

    return 1;
}
