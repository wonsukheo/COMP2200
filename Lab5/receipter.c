#include <stdio.h>
#include <time.h>
#include "receipter.h"
#include <string.h>

#define RECEIPT_WIDTH (51)

static char g_spacing[51];
char heading_buffer[256];
char* heading_buffer_ptr = heading_buffer;
char item_buffer[512];
char* item_buffer_ptr = item_buffer;

char tip_buffer[64];
char* tip_buffer_ptr = tip_buffer;

char total_buffer[512];
char* total_buffer_ptr = total_buffer;
char message_buffer[128];
char* message_buffer_ptr = message_buffer;
char ending_buffer[128];
char* ending_buffer_ptr = ending_buffer;

/* item_count reset on printing */
size_t item_count = 0u;
double subtotal = 0.00;
size_t order_number = 0u;

int add_item(const char* name, double price)
{ 
    int printed_item = 0;
    if (item_count >= 10) {
        return FALSE;
    }

    printed_item = sprintf(item_buffer_ptr, "%33s %16.2f\n", name, price);
    
    if (printed_item < 0) {
        return FALSE;
    } else {
        item_count++;
        subtotal += price;
        item_buffer_ptr += RECEIPT_WIDTH;
        return TRUE;
    }
}

void set_tip(double tip)
{

    if (tip != 0.00) {
        sprintf(tip_buffer_ptr, "%33s %16.2f\n", "Tip", tip);
        subtotal += tip;
    } else {
        tip_buffer_ptr = NULL;
    }
}

void set_total(void)
{
    size_t i;
    double tax = (subtotal * .05) + 0.005;
    
    for (i = 0; i < RECEIPT_WIDTH - 1; ++i) {
        g_spacing[i] = ' ';
    }
    g_spacing[i] = '\0';

    sprintf(total_buffer_ptr, "%50s\n", g_spacing);
    total_buffer_ptr += RECEIPT_WIDTH;
    sprintf(total_buffer_ptr, "%33s %16.2f\n", "Subtotal", subtotal);
    total_buffer_ptr += RECEIPT_WIDTH;
    
    if (tip_buffer_ptr != NULL) {    
        sprintf(total_buffer_ptr, "%50s\n", tip_buffer);
        total_buffer_ptr += RECEIPT_WIDTH;
    }
    sprintf(total_buffer_ptr, "%33s %16.2f\n", "Tax", tax);
    total_buffer_ptr += RECEIPT_WIDTH;
    sprintf(total_buffer_ptr, "%33s %16.2f\n", "Total", subtotal + tax);
    total_buffer_ptr += RECEIPT_WIDTH;
    sprintf(total_buffer_ptr, "%50s\n", g_spacing);
    total_buffer_ptr += RECEIPT_WIDTH;
}

void set_message(const char* message)
{
    /*size_t string_length = 0;
    size_t i;

    while (*message++ != '\0') {
        string_length++;
    }*/
        
    sprintf(message_buffer_ptr, "%-.50s\n", message);
    message_buffer_ptr += RECEIPT_WIDTH;
    
    if (strlen(message) > RECEIPT_WIDTH - 1) {
        sprintf(message_buffer_ptr, "%-.25s\n", message + RECEIPT_WIDTH - 1);
        message_buffer_ptr += 26;
    }
}

void set_ending(void)
{    
    size_t i;

    for (i = 0; i < RECEIPT_WIDTH - 1; ++i) {
        g_spacing[i] = '=';
    }
    g_spacing[i] = '\0';

    sprintf(ending_buffer_ptr, "%50s\n", g_spacing);
    ending_buffer_ptr += RECEIPT_WIDTH;
    sprintf(ending_buffer_ptr, "%50s\n", "Tax#-51234");
    ending_buffer_ptr += RECEIPT_WIDTH;
}

void set_heading(time_t timestamp)
{
    char time_string[48];
    size_t i;
    int hours, minutes, seconds, day, month, year;
    
    struct tm* gm = gmtime(&timestamp);

    hours = gm -> tm_hour;
    minutes = gm -> tm_min;
    seconds = gm -> tm_sec;
   
    day = gm -> tm_mday;
    month = gm -> tm_mon + 1;
    year = gm -> tm_year + 1900;
    
    


    sprintf(time_string, "%d-%02d-%02d %02d:%02d:%02d", year, month, day, hours, minutes, seconds);
    
    for (i = 0; i < RECEIPT_WIDTH - 1; ++i) {
        g_spacing[i] = '-';
    }
    g_spacing[i] = '\0';
        
    sprintf(heading_buffer_ptr, "%-50s\n", "Charles' Seafood");
    heading_buffer_ptr += RECEIPT_WIDTH;
    sprintf(heading_buffer_ptr, "%50s\n", g_spacing);
    heading_buffer_ptr += RECEIPT_WIDTH;
    sprintf(heading_buffer_ptr, "%-44s %05d\n", time_string, order_number);
    heading_buffer_ptr += RECEIPT_WIDTH;
    sprintf(heading_buffer_ptr, "%50s\n", g_spacing);
    heading_buffer_ptr += RECEIPT_WIDTH;
}

int print_receipt(const char* filename, time_t timestamp)
{
    FILE* stream;
    
    set_heading(timestamp);
    set_ending();
    set_total();
    
    if (item_buffer == item_buffer_ptr) {
        return 0;
    } 
    stream = fopen(filename, "w+");  
    fwrite(heading_buffer, sizeof(heading_buffer[0]), heading_buffer_ptr - heading_buffer, stream);
    fwrite(item_buffer, sizeof(item_buffer[0]), item_buffer_ptr - item_buffer, stream);
    fwrite(total_buffer, sizeof(total_buffer[0]), total_buffer_ptr - total_buffer, stream);
    fwrite(message_buffer, sizeof(message_buffer[0]), message_buffer_ptr - message_buffer, stream);
    fwrite(ending_buffer, sizeof(ending_buffer[0]), ending_buffer_ptr - ending_buffer, stream);
    fflush(stream);
    fclose(stream);

    order_number++;
    item_count = 0u;
    subtotal = 0.00;
    heading_buffer_ptr = heading_buffer;
    item_buffer_ptr = item_buffer;
    total_buffer_ptr = total_buffer;
    message_buffer_ptr = message_buffer;
    ending_buffer_ptr = ending_buffer;

    return 1;
}


