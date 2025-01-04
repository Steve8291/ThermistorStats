# ThermistorStats
## A mutable buffer that can quickly return standard deviation and median.
  - Intended to be used with raw .analogRead() integer values. Does not handle floats.
  - Buffer behaves circularly so adding more elements after it is full will replace earlier elements.
  - Using a while or if loop is the simplest way to fill buffer:
```c++
while (!my_buffer.isBufferFull) {
    my_buffer.add(value);
}
```
  - See examples folder for usage.