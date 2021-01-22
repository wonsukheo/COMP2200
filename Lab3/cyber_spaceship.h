#ifndef CYBER_SPACESHIP_H
#define CYBER_SPACESHIP_H

void update_overlapped_count(const size_t cluster_count, const char* const cluster_start_location[], const size_t cluster_lengths[], const char* current_location, size_t* overlapped_count);

const char* update_longest_safe_area_length(size_t safe_area_length, size_t* longest_safe_area_length, const char* current_location, const char* longest_safe_area);

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length);

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count);

#endif /* CYBER_SPACESHIP */
