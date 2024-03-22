# Pràctica 1 : BLINK 

## Objetivo:
- El objetivo de la practica es producir el parpadeo periodico de un led. Se utilizara la salida serie para
depurar el programa.

## Materiales: 
- ESP32-S1 
- LED (rojo)
## Procedimiento: 
### Con delay: 
**Codigo:**
```cpp
    #define LED_BUILTIN 23
    #define DELAY 500

    void setup()
    {
        Serial.begin(115200); 
        // Inializa la comunicación serial la velocidad (baudios)
        pinMode(LED_BUILTIN, OUTPUT);
        // Configura el pin como salida del led integrado
    }
    void loop()
    {
        digitalWrite(LED_BUILTIN, HIGH); // Enciende el LED 
        Serial.println("ON"); // Mostrar por pantalla 
        delay(500); // Espera (en segundos)
        digitalWrite(LED_BUILTIN, LOW); // Apaga el LED
        Serial.println("OFF");  
        delay(500);
    }
```
**Descripcion:** <br>
Este codigo enciende y apaga un led  integrado de manera repetitiva con una frecuencia de 1/2 segundo. La variable "DELAY" es utilizada para crear una "separacion temporal" en el proceso del led, es decir, se encenderá y apagará separadamente en el periodo de tiempo marcado. 

**Diagrama de flujos:**

``` mermaid 
graph LR
    A[Setup] --> B[Loop]
    B --> C[Turn ON LED]
    C --> D[Print ON]
    D --> E[Delay 500 ms]
    E --> F[Turn OFF LED]
    F --> G[Print OFF]
    G --> H[Delay 500 ms]
    H --> B
```

**Diagrama de tiempo:**
``` mermaid
sequenceDiagram
    participant Arduino as ESP-32 Board
    participant Serial as Serial Monitor
    participant LED as Built-in LED
    Arduino->>LED: digitalWrite(LED_BUILTIN, HIGH)
    LED->>Arduino: State = ON
    Arduino->>Serial: Serial.println("ON")
    Serial->>Arduino: Receive "ON"
    Arduino->>LED: delay(500)
    LED->>Arduino: State = ON
    Arduino->>LED: digitalWrite(LED_BUILTIN, LOW)
    LED->>Arduino: State = OFF
    Arduino->>Serial: Serial.println("OFF")
    Serial->>Arduino: Receive "OFF"
    Arduino->>LED: delay(500)
    LED->>Arduino: State = OFF
```


### Sin delay: 
**Código:**
```cpp
    #define LED_BUILTIN 23
    #define DELAY 500

    void setup()
    {
        Serial.begin(115200); 
        // Inializa la comunicación serial la velocidad (baudios)
        pinMode(LED_BUILTIN, OUTPUT);
        // Configura el pin como salida del led integrado
    }
    void loop()
    {
        digitalWrite(LED_BUILTIN, HIGH); // Enciende el LED 
        Serial.println("ON"); // Mostrar por pantalla 
        // delay(500); // Sin delay
        digitalWrite(LED_BUILTIN, LOW); // Apaga el LED
        Serial.println("OFF");  
        // delay(500);
    }
```
**Descripcion:** <br>
En este caso, el led se endenderá y apagará repetitivamente sin ninguna separación temporal, es decir,  no habrá un "delay" entre cada cambio.

**Diagrama de flujos:**

``` mermaid 
graph LR
    A[Setup] --> B[Loop]
    B --> C[Turn ON LED]
    C --> D[Print ON]
    D --> E[Turn OFF LED]
    E --> F[Print OFF]
    F --> G[Loop]
    G --> B
 ```
 **Diagrama de tiempo:**

 ``` mermaid
 sequenceDiagram
    participant Arduino as ESP-32 Board
    participant Serial as Serial Monitor
    participant LED as Built-in LED
    Arduino->>LED: digitalWrite(LED_BUILTIN, HIGH)
    LED->>Arduino: State = ON
    Arduino->>Serial: Serial.println("ON")
    Serial->>Arduino: Receive "ON"
    Arduino->>LED: digitalWrite(LED_BUILTIN, LOW)
    LED->>Arduino: State = OFF
    Arduino->>Serial: Serial.println("OFF")
    Serial->>Arduino: Receive "OFF"
    Arduino->>LED: digitalWrite(LED_BUILTIN, HIGH)
    LED->>Arduino: State = ON
    Arduino->>Serial: Serial.println("ON")
    Serial->>Arduino: Receive "ON"
    Arduino->>LED: digitalWrite(LED_BUILTIN, LOW)
    LED->>Arduino: State = OFF
    Arduino->>Serial: Serial.println("OFF")
    Serial->>Arduino: Receive "OFF"
 ```
### Sin delay. Modificar la salida a uno cualquiera de los que estan disponibles y medir con el osciloscopio la máxima frecuencia de apagado y encendido que permite el microcontrolador. En 4 casos: 
- **Con el envio por el puerto série del mensaje i utilizando las funciones de Arduino**
```cpp
   #include <Arduino.h>

   #define LED_BUILTIN 23

   void setup() {                
      pinMode(LED_BUILTIN, OUTPUT);   
      Serial.begin(115200);
   }

   void loop() {
      Serial.println("ON");
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("OFF");      
      digitalWrite(LED_BUILTIN, LOW);
   }
   ```
Frecuencias: 34,0us o 29,2khz .

- **Con el envio por el puerto série y accedirendo directamente a los registros:**
```cpp
    #include <Arduino.h>

    #define LED_BUILTIN 23
    uint32_t *gpio_out = (uint32_t *)GPIO_OUT_REG;

    void setup() {                
        pinMode(LED_BUILTIN, OUTPUT);   
        Serial.begin(115200);
    }

    void loop() {
        Serial.println("ON");
        *gpio_out |= (1 << LED_BUILTIN);
        Serial.println("OFF");      
        *gpio_out ^= (1 << LED_BUILTIN);
    }
```
Frecuencias: 34.2us o 29.2khz
```cpp
    *gpio_out |= (1 << LED_BUILTIN); 
    // Establece el bit correspondiente al LED_BUILTIN en el registro de salida GPIO (*gpio_out). La expresión (1 << LED_BUILTIN) desplaza un bit a la izquierda por el número de posiciones especificado por LED_BUILTIN. Esto significa que se coloca un 1 en la posición del pin LED_BUILTIN en el registro de salida GPIO. Luego, el operador de asignación por OR (|=) se utiliza para establecer ese bit en 1 sin afectar los otros bits del registro de salida GPIO.

    *gpio_out ^= (1 << LED_BUILTIN); 
    // Invierte el estado del bit correspondiente al LED_BUILTIN en el registro de salida GPIO. La expresión (1 << LED_BUILTIN) nuevamente coloca un 1 en la posición del pin LED_BUILTIN en el registro de salida GPIO. Luego, el operador XOR (^=) se utiliza para invertir el estado del bit en esa posición. Si el bit estaba en 1, se cambia a 0; si estaba en 0, se cambia a 1. Esto efectivamente cambia el estado del LED conectado al pin LED_BUILTIN de encendido a apagado o viceversa, dependiendo de su estado actual.
```
 - **Sin el envio por el puerto série del mensaje i utilizando las funciones de Arduino:**
```cpp
    #include <Arduino.h>
    #define LED_BUILTIN 23

    void setup() {                
    pinMode(LED_BUILTIN, OUTPUT);   
    }

    void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(LED_BUILTIN, LOW);
    }
   ```
Frecuencias: 568ns o 1.76Mhz

 - **Sin el envio por el puerto série y accedirendo directamente a los registros:**
```cpp
    #include <Arduino.h>

    #define LED_BUILTIN 23
    uint32_t *gpio_out = (uint32_t *)GPIO_OUT_REG;

    void setup() {                
    pinMode(LED_BUILTIN, OUTPUT);   
    }

    void loop() {
    *gpio_out |= (1 << LED_BUILTIN);
    *gpio_out ^= (1 << LED_BUILTIN);
    }
```
Frecuencia: 212ns o 4.717Mhz.

## Pregunta / Observación : 
**¿ En el programa que se ha realizado cual es el tiempo libre que tiene el procesador ?**
Podemos definir como tiempo libro del procesador cuando este no hace nada. Cuando en el programa metiamos un delay (#define DELAY 500) es un claro ejemplo de tiempo libre, ya que en esos microsegundos el programa no hacia nada, tenia tiempo libre. 

##
El microcontrolador ESP32 es muy similar a Arduino, los diagramas de tiempo muestran las interacciones realizadas entre el microcontrolador, el LED, el "serial monitor, consquentemente, lo mismo pasaria con un programa de Arduino. En este caso, tienen unas diferencias insificantes, como que quizàs en el caso de Arduino tendriamos que conectar el LED en diferente pin que al ESP32. Diferencia que no afecta a nuestro dragrama de tiempo. 

## Conclusión:
Hemos controlado el estado del pin conectado al LED integrado y enviado mensajes a través del puerto serial para monitorear el estado del LED. Esto proporciona una forma básica de interactuar con el hardware y realizar operaciones simples utilizando el ESP32 y la plataforma de desarrollo Arduino.



