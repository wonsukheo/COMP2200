#include "cyber_spaceship.h"

void update_overlapped_count(const size_t cluster_count, const char* const cab_start_location, char* current_location, size_t* overlapped_count)
{
     for (j = 0; j < cluster_count; ++j) {
         if (current_location == cluster_start_locations[j]) {
             overlapped_count* += 1;
         } 
         if (current_location == &cluster_start_locations[j] + cluster_lengths[j]) {
             overlapped_count* = 0;
             }
     } 
}

void update_longest_safe_area_length(size_t safe_area_length, size_t longest_safe_area_length, char* current location)
{
     if (safe_area_length >= longest_safe_area_length) {
         longest_safe_area_length = safe_area_length;
         longest_safe_area = current_location;
     }
}
            
const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{
            size_t safe_area_length = 0;
            size_t longest_safe_area_length = 0;
            char* longest_safe_area;
            size_t overlapped_count = 0;
            char* current_location = &cab_start_location; 
            size_t i;
            size_t j;

           
            
            for (i = 0; i < cab_length; ++i) {
                 update_overlapped_count(cluster_count, cab_start_location, current_location, &overlapped_count);
                 
                 if (overlapped_count == 0 || (overlapped_count % 2 = 0) {
                     safe_area_length += 1;
                 } 
                 if (overlapped_count % 2 != 0) {
                     update_longest_safe_area_length(safe_area_length, longest_safe_area_length, current location);
                     safe_area_length = 0;
                 }
               
                 ++current location;
            }
 
            UPDATE_LONGEST_SAFE_AREA_LENGTH();
            
            out_longest_safe_area_length* = safe_area_length;
            
            return longest_safe_area - longest_safe_area_length;
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{
    char* current_location = &cab_start_location; 
    size_t overlapped_count = 0;
    double travel_time = 0;
    const double safe_area_travel_speed = 0.2;
    const double cluster_area_travel_speed = 0.1;
    size_t i;

    for (i = 0; i < cab_length; ++i) {
        update_overlapped_count(cluster_count, cab_start_location, current_location, &overlapped_count);
        
        if (overlapped_count == 0 || (overlapped_count % 2 = 0) {
            travel_time += 0.1;
        } 
        if (overlapped_count % 2 != 0) {
            travel_time += 0.2;
        }
        ++ current location;
    }    
    
    return (int)(travel_time + 0.5);
}
