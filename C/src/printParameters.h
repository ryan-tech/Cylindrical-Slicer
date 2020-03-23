#ifndef PRINTPARAMETERS_H
#define PRINTPARAMETERS_H

#include <string.h>

class printParameters
{
public:
    printParameters();

    float getFilament() {return m_filament;}
    float getExtruderTemp() {return m_extruderTemp;}
    float getBedTemp() {return m_bedTemp;}
    float getLayerHeight() {return m_layerHeight;}
    float getFirstLayerHeight() {return m_firstLayerHeight;}
    float getZOffset() {return m_zOffset;}
    float getTravelSpeed() {return m_travelSpeed;}
    float getFirstLayerSpeed() {return m_firstLayerSpeed;}
    float getPrintSpeed() {return m_printSpeed;}
    string getOutputFileName() {return outputFileName;}

    void setFilament(float filament) {m_filament = filament;}
    void setExtruderTemp(float temp) {m_extruderTemp = temp;}
    void setBedTemp(float temp) {m_bedTemp = temp;}
    void setLayerHeight(float height) {m_layerHeight = height;}
    void setFirstLayerHeight(float height) {m_firstLayerHeight = height;}
    void setZOffset(float offset) {m_zOffset = offset;}
    void setTravelSpeed(float speed) {m_travelSpeed = speed;}
    void setFirstLayerSpeed(float speed) {m_firstLayerSpeed = speed;}
    void setPrintSpeed(float speed) {m_printSpeed = speed;}
    void setOutputFileName(string name) {outputFileName = name;}
private:
    float m_filament;
    float m_extruderTemp;
    float m_bedTemp;
    float m_layerHeight;
    float m_firstLayerHeight;
    float m_zOffset;
    float m_travelSpeed;
    float m_firstLayerSpeed;
    float m_printSpeed;
    string outputFileName;

};

#endif
