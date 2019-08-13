/**
 * @reference https://github.com/myDevicesIoT/cayenne-docs/blob/master/docs/LORA.md
 * @reference http://openmobilealliance.org/wp/OMNA/LwM2M/LwM2MRegistry.html#extlabel
 *
 * Adapted for lora-app-server from https://gist.github.com/iPAS/e24970a91463a4a8177f9806d1ef14b8
 *
 * Type                 IPSO    LPP     Hex     Data Size   Data Resolution per bit
 *  Digital Input       3200    0       0       1           1
 *  Digital Output      3201    1       1       1           1
 *  Analog Input        3202    2       2       2           0.01 Signed
 *  Analog Output       3203    3       3       2           0.01 Signed
 *  Illuminance Sensor  3301    101     65      2           1 Lux Unsigned MSB
 *  Presence Sensor     3302    102     66      1           1
 *  Temperature Sensor  3303    103     67      2           0.1 °C Signed MSB
 *  Humidity Sensor     3304    104     68      1           0.5 % Unsigned
 *  Accelerometer       3313    113     71      6           0.001 G Signed MSB per axis
 *  Barometer           3315    115     73      2           0.1 hPa Unsigned MSB
 *  Time                3333    133     85      4           Unix time MSB
 *  Gyrometer           3334    134     86      6           0.01 °/s Signed MSB per axis
 *  GPS Location        3336    136     88      9           Latitude  : 0.0001 ° Signed MSB
 *                                                          Longitude : 0.0001 ° Signed MSB
 *                                                          Altitude  : 0.01 meter Signed MSB
 *
 * Additional types
 *  Generic Sensor      3300    100     64      4           Unsigned integer MSB
 *  Voltage             3316    116     74      2           0.01 V Unsigned MSB
 *  Current             3317    117     75      2           0.001 A Unsigned MSB
 *  Frequency           3318    118     76      4           1 Hz Unsigned MSB
 *  Percentage          3320    120     78      1           1% Unsigned
 *  Altitude            3321    121     79      2           1m Signed MSB
 *  Power               3328    128     80      2           1 W Unsigned MSB
 *  Distance            3330    130     82      4           0.001m Unsigned MSB
 *  Energy              3331    131     83      4           0.001kWh Unsigned MSB
 *  Direction           3332    132     84      2           1º Unsigned MSB
 *  Switch              3342    142     8E      1           0/1
 * 
 */

// lppDecode decodes an array of bytes into an array of ojects, 
// each one with the channel, the data type and the value.
function lppDecode(bytes) {
    
    var sensor_types = {
        0  : {'size': 1, 'name': 'digital_input', 'signed': false, 'divisor': 1},
        1  : {'size': 1, 'name': 'digital_output', 'signed': false, 'divisor': 1},
        2  : {'size': 2, 'name': 'analog_input', 'signed': true , 'divisor': 100},
        3  : {'size': 2, 'name': 'analog_output', 'signed': true , 'divisor': 100},
        4  : {'size': 2, 'name': 'counter', 'signed': false, 'divisor': 1},
        100: {'size': 4, 'name': 'generic', 'signed': false, 'divisor': 1},
        101: {'size': 2, 'name': 'illuminance', 'signed': false, 'divisor': 1},
        102: {'size': 1, 'name': 'presence', 'signed': false, 'divisor': 1},
        103: {'size': 2, 'name': 'temperature', 'signed': true , 'divisor': 10},
        104: {'size': 1, 'name': 'humidity', 'signed': false, 'divisor': 2},
        113: {'size': 6, 'name': 'accelerometer', 'signed': true , 'divisor': 1000},
        115: {'size': 2, 'name': 'barometer', 'signed': false, 'divisor': 10},
        116: {'size': 2, 'name': 'voltage', 'signed': false, 'divisor': 100},
        117: {'size': 2, 'name': 'current', 'signed': false, 'divisor': 1000},
        118: {'size': 4, 'name': 'frequency', 'signed': false, 'divisor': 1},
        120: {'size': 1, 'name': 'percentage', 'signed': false, 'divisor': 1},
        121: {'size': 2, 'name': 'altitude', 'signed': true, 'divisor': 1},
        128: {'size': 2, 'name': 'power', 'signed': false, 'divisor': 1},
        130: {'size': 4, 'name': 'distance', 'signed': false, 'divisor': 1000},
        131: {'size': 4, 'name': 'energy', 'signed': false, 'divisor': 1000},
        132: {'size': 1, 'name': 'direction', 'signed': false, 'divisor': 1},
        133: {'size': 4, 'name': 'time', 'signed': false, 'divisor': 1},
        134: {'size': 6, 'name': 'gyrometer', 'signed': true , 'divisor': 100},
        136: {'size': 9, 'name': 'location', 'signed': true, 'divisor': [10000,10000,100]},
        142: {'size': 1, 'name': 'switch', 'signed': false, 'divisor': 1},
    };

    function arrayToDecimal(stream, is_signed, divisor) {

        var value = 0;
        for (var i = 0; i < stream.length; i++) {
            if (stream[i] > 0xFF)
                throw 'Byte value overflow!';
            value = (value << 8) | stream[i];
        }

        if (is_signed) {
            var edge = 1 << (stream.length) * 8;  // 0x1000..
            var max = (edge - 1) >> 1;             // 0x0FFF.. >> 1
            value = (value > max) ? value - edge : value;
        }

        value /= divisor;

        return value;

    }

    var sensors = [];
    var i = 0;
    while (i < bytes.length) {

        var s_no   = bytes[i++];
        var s_type = bytes[i++];
        if (typeof sensor_types[s_type] == 'undefined') {
            throw 'Sensor type error!: ' + s_type;
        }

        var s_value = 0;
        var type = sensor_types[s_type];
        switch (s_type) {

            case 113:   // Accelerometer
            case 134:   // Gyrometer
                s_value = {
                    'x': arrayToDecimal(bytes.slice(i+0, i+2), type.signed, type.divisor),
                    'y': arrayToDecimal(bytes.slice(i+2, i+4), type.signed, type.divisor),
                    'z': arrayToDecimal(bytes.slice(i+4, i+6), type.signed, type.divisor)
                };
                break;
            
            case 136:   // GPS Location
                s_value = {
                    'latitude': arrayToDecimal(bytes.slice(i+0, i+3), type.signed, type.divisor[0]),
                    'longitude': arrayToDecimal(bytes.slice(i+3, i+6), type.signed, type.divisor[1]),
                    'altitude': arrayToDecimal(bytes.slice(i+6, i+9), type.signed, type.divisor[2])
                };
                break;

            default:    // All the rest
                s_value = arrayToDecimal(bytes.slice(i, i + type.size), type.signed, type.divisor);
                break;
        }
        
        sensors.push({
            'channel': s_no,
            'type': s_type,
            'name': type.name,
            'value': s_value
        });

        i += type.size;

    }

    return sensors;

}

// To use with TTN
function Decoder(bytes, fPort) {
    
    // flat output (like original decoder):
    var response = {};
    lppDecode(bytes, 1).forEach(function(field) {
        response[field['name'] + '_' + field['channel']] = field['value'];
    });
    return response;

    // field output
    //return {'fields': lppDecode(bytes, fPort)};

}

// To use with NodeRED
// Assuming msg.payload contains the LPP-encoded byte array
/*
msg.fields = lppDecode(msg.payload);
return msg;
*/