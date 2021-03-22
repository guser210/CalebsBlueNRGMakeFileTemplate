#ifdef __cplusplus
extern "C" {
#endif
#include "Bluetooth.h"
#include "bluenrg1_api.h"
#include "BlueNRG1_sysCtrl.h"

#include <string.h>

#include "ble_const.h"

#ifdef __cplusplus
}
#endif


Bluetooth::Bluetooth(   char *name   )
{
    memset(deviceName, 0, sizeof(deviceName));
    memcpy( deviceName, name, strlen(name));


}

Bluetooth::~Bluetooth()
{
}

void Bluetooth::InitDevice(){
    aci_hal_write_config_data(0, sizeof(deviceAddress), deviceAddress);

    aci_hal_set_tx_power_level(1,4);

    aci_gatt_init();

    aci_gap_init(1, 0, sizeof( deviceName), &gapServiceHandle, &gapCharHandle, &gapCharAppearanceHandle);

    aci_gatt_update_char_value_ext(0, gapServiceHandle, gapCharHandle, 0, sizeof(deviceName), 0, sizeof(deviceName), deviceName);

}

void Bluetooth::AddService(){
    uint8_t ret = 0;

    Service_UUID_t sid;
    memcpy(&sid.Service_UUID_16, serviceID, 2);
    ret = aci_gatt_add_service(UUID_TYPE_16, &sid,
                                  1, 5, &serviceHandle);  

    serial.SendMessage("service = x%02x\r",ret);

    Char_UUID_t cid;
    memcpy(&cid.Char_UUID_16, charID, 2);
    aci_gatt_add_char(serviceHandle,
                    UUID_TYPE_16,
                    &cid,
                    20,
                    CHAR_PROP_NOTIFY | CHAR_PROP_READ | CHAR_PROP_WRITE_WITHOUT_RESP,
                    0,
                    GATT_NOTIFY_ATTRIBUTE_WRITE,
                    16, 1, &charHandle);
    serial.SendMessage("char = x%02x\r",ret);


    uint8_t desc1[30] =  {"guser210 AT Command Interface"};
    Char_Desc_Uuid_t cdid;
    uint16_t descid = CHAR_USER_DESC_UUID;
    memcpy( &cdid.Char_UUID_16, &descid, 2);
    aci_gatt_add_char_desc(serviceHandle, 
                        charHandle,
                        UUID_TYPE_16,
                        &cdid,
                        sizeof(desc1),
                        sizeof(desc1),
                        desc1,
                        0, 1,0, 16, 0, &descHandle);
    serial.SendMessage("desc = x%02x\r",ret);
}

void Bluetooth::Tick(){

    uint8_t mdata[6 + sizeof(deviceName)] = {
        3, 3, 0xe0, 0xaa,
        sizeof(deviceName) + 1,
        9
    };

    memcpy(mdata + 6, deviceName, sizeof(deviceName));

    hci_le_set_scan_response_data(sizeof(mdata), mdata);

    aci_gap_set_discoverable(ADV_IND, 100, 100, 0, 0, 
                            sizeof(deviceName), deviceName, 0, NULL, 0, 0);

    aci_gap_update_adv_data(sizeof(mdata), mdata);                            

}