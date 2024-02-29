# Pràctica 1 : BLINK 
## Con delay: 
**Codigo:**

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

Este codigo enciende y apaga un led  integrado de manera repetitiva con una frecuencia de 1/2 segundo. La variable "DELAY" es utilizada para

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
```


## Sin delay: 
**Código:**
    
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