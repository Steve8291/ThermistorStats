#include <ThermistorStats.h>

ThermistorStats::ThermistorStats(int buffer_size)
    : _size(buffer_size), _data_array(buffer_size) {}

void ThermistorStats::resize(int buffer_size) {
    _size = buffer_size;
    _buffer_full = false;
    _element = 0;
    _data_sorted = false;
    _data_ordered = true;
    _data_array.resize(buffer_size);
    fill(_data_array.begin(), _data_array.end(), 0);  // Zero all values in new vector.
}

void ThermistorStats::add(int16_t value) {
    _data_array[_element] = value;
    if (_element < _size - 1) {
        _element++;
        _buffer_full = false;
        _data_sorted = false;
    } else {
        _element = 0;
        _buffer_full = true;
    }
}

// Uses the nth_element algorithm to limit cost of sorting all data.
// Returns int16_t median for odd size buffers.
// Even buffers are average of two numbers rounded.
// Returns -1 in case buffer hasn't been filled.
int16_t ThermistorStats::getMedian() {
    int16_t median;
    if (!_buffer_full) return -1;

    if (!_data_sorted) {
        if (_size % 2 == 1) {
            nth_element(_data_array.begin(), _data_array.begin() + _size / 2, _data_array.end());
            median = _data_array[_size / 2];
        } else {
            nth_element(_data_array.begin(), _data_array.begin() + _size / 2 - 1, _data_array.end());
            median = (_data_array[_size / 2 - 1] + _data_array[_size / 2]) / 2.0 + 0.5;  // +0.5 used to round to int
        }
    } else {
        if (_size % 2 == 1) {
            median = _data_array[_size / 2];
        } else {
            median = (_data_array[_size / 2 - 1] + _data_array[_size / 2]) / 2.0 + 0.5;  // +0.5 used to round to int
        }
    }
    _data_ordered = false;
    return median;
}

bool ThermistorStats::isBufferFull() const {
    return _buffer_full;
}

float ThermistorStats::getStdDev() const {
    float std_dev = -1;  // Default value if buffer not full.
    if (_buffer_full) {
        float sum = 0;
        for (int i = 0; i < _size; ++i) {
            sum += _data_array[i];
        }
        float mean = sum / _size;
        float sq_dev_sum = 0;
        for (int i = 0; i < _size; ++i) {
            float deviation = _data_array[i] - mean;
            sq_dev_sum += deviation * deviation;
        }
        std_dev = sqrt(sq_dev_sum / _size);
    }
    return std_dev;
}

// Returns 0 for any missing values when buffer is not full.
// Returns -1 for all values if called after getSortedElement() or getMedian()
int16_t ThermistorStats::getElement(int element) const {
    if (!_data_ordered) return -1;
    else return _data_array[element];
}

// Returns 0 for any missing values when buffer is not full.
int16_t ThermistorStats::getSortedElement(int element) {
    if (!_data_sorted) {
        sort(_data_array.begin(), _data_array.end());
        _data_sorted = true;
        _data_ordered = false;
    }
    return _data_array[element];
}

int _size;
std::vector<int16_t> _data_array;
int _element = 0;
bool _buffer_full = false;
bool _data_sorted = false;
bool _data_ordered = true;  // Is data in original order for getElement()
