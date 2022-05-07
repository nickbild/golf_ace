#define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static inline
#define __SSAT(ARG1, ARG2) \
__extension__ \
({                          \
  int32_t __RES, __ARG1 = (ARG1); \
  __ASM volatile ("ssat %0, %1, %2" : "=r" (__RES) :  "I" (ARG2), "r" (__ARG1) : "cc" ); \
  __RES; \
 })
 
#include <stdio.h>
#include <ai_golf_inferencing.h>
#include "edge-impulse-sdk/classifier/ei_run_classifier.h"

#include "edge-impulse-sdk/porting/ei_classifier_porting.h"

#include "edge-impulse-sdk/dsp/kissfft/kiss_fftr.h"

#include <Adafruit_NeoPixel.h>

#define PIN        6

Adafruit_NeoPixel pixels(1, PIN, NEO_GRB + NEO_KHZ800);
#include <Arduino_LSM6DS3.h>



















// Callback function declaration
static int get_signal_data(size_t offset, size_t length, float *out_ptr);

// Raw features copied from test sample
float features[375] = {};

int inference(void) {
    
    signal_t signal;            // Wrapper for raw input buffer
    ei_impulse_result_t result; // Used to store inference output
    EI_IMPULSE_ERROR res;       // Return code from inference

    // Calculate the length of the buffer
    size_t buf_len = sizeof(features) / sizeof(features[0]);

    // Make sure that the length of the buffer matches expected input length
    if (buf_len != EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE) {
        printf("ERROR: The size of the input buffer is not correct.\r\n");
        printf("Expected %d items, but got %d\r\n", 
                EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, 
                (int)buf_len);
        return 1;
    }

    // Assign callback function to fill buffer used for preprocessing/inference
    signal.total_length = EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE;
    signal.get_data = &get_signal_data;

    // Perform DSP pre-processing and inference
    res = run_classifier(&signal, &result, false);

    // Print return code and how long it took to perform inference
    printf("run_classifier returned: %d\r\n", res);
    printf("Timing: DSP %d ms, inference %d ms, anomaly %d ms\r\n", 
            result.timing.dsp, 
            result.timing.classification, 
            result.timing.anomaly);



    // Print anomaly result (if it exists)

    printf("Anomaly prediction: %.3f\r\n", result.anomaly);
    Serial.println(result.anomaly);

    if (result.anomaly > 1) {
      Serial.println("ANOMALY *****************");
      pixels.setPixelColor(0, pixels.Color(150, 0, 0));
      pixels.show();
      delay(2000);
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.show();

    } else {
      Serial.println("PRO ********************");
      pixels.setPixelColor(0, pixels.Color(0, 150, 0));
      pixels.show();
      delay(2000);
      pixels.setPixelColor(0, pixels.Color(0, 0, 0));
      pixels.show();
    }


    return 0;
}

// Callback: fill a section of the out_ptr buffer when requested
static int get_signal_data(size_t offset, size_t length, float *out_ptr) {
    for (size_t i = 0; i < length; i++) {
        out_ptr[i] = (features + offset)[i];
    }

    return EIDSP_OK;
}

void setup() {
  Serial.begin(115200);

  pinMode(12, INPUT_PULLDOWN);
  
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);

  pixels.begin();

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }
  
}

void loop() {
  Serial.println("Hi");

  if (digitalRead(12) == HIGH) {
    Serial.println("button pressed");
    getAccelData();
    inference();
  }
  
}

void getAccelData() {
  float x, y, z;
  int cnt = 0;
  int idx = 0;
  
  while (true) {
    if (IMU.accelerationAvailable()) {
      IMU.readAcceleration(x, y, z);
  
      Serial.print(x);
      Serial.print('\t');
      Serial.print(y);
      Serial.print('\t');
      Serial.println(z);

      features[idx] = x;
      idx++;
      features[idx] = y;
      idx++;
      features[idx] = z;
      idx++;

      cnt += 1;
      if (cnt >=125) {
        break;  
      }
    }
  }
}
