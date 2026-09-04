# TIM2 Interrupt Architecture

```text
TIM2 counter
    |
    | update event
    v
TIM2_SR.UIF
    |
    | interrupt request enabled by TIM2_DIER.UIE
    v
NVIC ISER0 bit 28
    |
    v
TIM2_IRQHandler()
    |
    +--> check UIF
    +--> clear UIF
    +--> perform minimal ISR work
    +--> signal application/event state
    |
    v
main loop / application
```

## Design rule
The interrupt service routine should remain short and deterministic. Avoid long delays, blocking operations and complex application logic inside the ISR.

## Polling versus interrupt
Polling keeps the CPU checking a status bit. Interrupt mode lets the timer hardware request CPU service only when the event occurs, allowing the main loop to perform other work between events.
