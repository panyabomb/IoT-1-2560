import time
import sys
import Adafruit_DHT
import http.client, urllib

# Sensor should be set to Adafruit_DHT.DHT11,
# Adafruit_DHT.DHT22, or Adafruit_DHT.AM2302.
sensor = Adafruit_DHT.DHT22

# Example using a Beaglebone Black with DHT sensor
# connected to pin P18.
pin = 16

# Example using a Raspberry Pi with DHT sensor
# connected to GPIO23.
#pin = 23

key = 'RQAM9KQTBB0SDF5Q'  # Thingspeak channel to update

# Note that sometimes you won't get a reading and
# the results will be null (because Linux can't
# guarantee the timing of calls to read the sensor).
# If this happens try again!
if __name__ == '__main__':     # Program start from here
    try:
        while(True):
            # Try to grab a sensor reading.  Use the read_retry method which will retry up
            # to 15 times to get a sensor reading (waiting 2 seconds between each retry).
            humidity, temperature = Adafruit_DHT.read_retry(sensor, pin)
            if humidity is not None and temperature is not None:
                print('Temp={0:0.1f}*C  Humidity={1:0.1f}%'.format(temperature, humidity))
                params = urllib.parse.urlencode({'field1': temperature, 'field2':humidity ,'key':key}) 
                headers = {"Content-typZZe": "application/x-www-form-urlencoded","Accept": "text/plain"}
                conn = http.client.HTTPConnection("api.thingspeak.com:80")
                try:
                    conn.request("POST", "/update", params, headers)
                    response = conn.getresponse()
                    #print temp
                    print (response.status, response.reason)
                    data = response.read()
                    conn.close()
                except:
                    print("connection failed")
                    break
            else:
                print('Failed to get reading. Try again!')
            time.sleep(10)
    except KeyboardInterrupt:  # When 'Ctrl+C' is pressed, the child program destroy() will be  executed
        sys.exit(0)
