function Decoder(bytes, port) {
  // Decode an uplink message from a buffer
  // (array) of bytes to an object of fields.
  var decoded = {};

  // if (port === 1) decoded.led = bytes[0];
  if (port == 10) {
    decoded.temperature = (bytes[1] + bytes[0]*256)/100.0;
    decoded.pressure = (bytes[4] + bytes[3]*256 + bytes[2]*256*256) / 100.0;
    decoded.humidity = bytes[5];
  } else if (port == 11) {
    decoded.rotation = bytes[0];
  } else if (port == 12) {
    decoded.air_quality = (bytes[1] + bytes[0]*256);
  } else if (port == 16) {
    decoded.motion = bytes[0];
  } else if (port == 20) {
    decoded.loudness = (bytes[1] + bytes[0]*256);
  } else if (port == 21) {    // sunlight sensor
    decoded.visible_light = (bytes[1] + bytes[0]*256);
    decoded.infrared_light = (bytes[3] + bytes[2]*256);
    decoded.ultraviolet_light = (bytes[5] + bytes[4]*256) / 100;
  } else if (port == 26) {
    // Ultrasonic distance
    decoded.distance = (bytes[0] + bytes[1]*256);
  } else if (port == 17 || port == 28 || port == 31) {
    decoded.state = (bytes[0] == 0xFF ? true : false);
    decoded.event = true;
  } else if (port == 25) {
    var id = "";
    for (var i = 0; i < bytes.length; i++) {
      id += String.fromCharCode(bytes[i]);
    }
    decoded.id = id;
    decoded.single_byte = bytes[0] | bytes[1];
  } else if (port == 27) {
    decoded.switchvalue = bytes[0];
  } else if (port == 29) {
    decoded.temperature = (bytes[1] + bytes[0]*256)/100.0;
    decoded.humidity = (bytes[3] + bytes[2]*256)/100.0;
  } else if (port == 30) {
    decoded.gas_density = (bytes[1] + bytes[0]*256)/1000.0;
  } else if (port == 31) {
    decoded.switchvalue = bytes[0];
  }

  return decoded;
}