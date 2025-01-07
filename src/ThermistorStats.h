#ifndef THERMISTORSTATS_H
#define THERMISTORSTATS_H

#include <Arduino.h>
#include <vector>
#include <algorithm>

class ThermistorStats {
public:
    ThermistorStats(int buffer_size);

    // Resize the buffer
    void resize(int buffer_size);

    // Add sensor reading to array
    void add(int16_t value);

    // Uses the nth_element algorithm to limit cost of sorting all data.
    // Returns int16_t median for odd size buffers.
    // Even buffers are average of two numbers rounded.
    // Returns -1 in case buffer hasn't been filled.
    int16_t getMedian();

    bool isBufferFull() const;

    float getStdDev();

    // Serial.print average of last 3 elements --> List of first elements less than avg.
    // Used to determine if enough time has elapsed to charge capacitor.
    // If cap delay is long enough you will see only an occasional 1 or 2 items in list.
    void compareFirstLast() const;

    // Returns 0 for any missing values when buffer is not full.
    // Returns -1 for all values if called after getSortedElement() or getMedian()
    int16_t getElement(int element) const;

    // Returns 0 for any missing values when buffer is not full.
    int16_t getSortedElement(int element);

    // Zeros the buffer and sets .isBufferFull(false);
    void zeroBuffer();

private:
    std::vector<int16_t> _data_array;
    int _size;
    int _element;
    bool _buffer_full;
    bool _data_sorted;
    bool _data_ordered;
};

#endif