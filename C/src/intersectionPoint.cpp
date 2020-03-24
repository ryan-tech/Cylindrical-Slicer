#include "intersectionPoint.h"

intersetionPoint::intersetionPoint(){
    m_xVal = 0;
    m_yVal = 0;
    m_zVal = 0;
    m_eVal = 0;
    m_fVal = 0;
    m_extrude = 0;
    m_next = NULL;
}
intersetionPoint::intersetionPoint(float x, float y, float z){
    m_xVal = x;
    m_yVal = y;
    m_zVal = z;
    m_eVal = 0;
    m_fVal = 0;
    m_extrude = 0;
    m_next = NULL;
}
intersetionPoint::intersetionPoint(float x, float y, float z, float e, float f, bool extrude){
    m_xVal = x;
    m_yVal = y;
    m_zVal = z;
    m_eVal = e;
    m_fVal = f;
    m_extrude = extrude;
    m_next = NULL;
}

void intersetionPoint::generateGcodeCommand(){
    //string command;

    //G1 X113.024 Y80.727 E2.38174 F1800.000
}

//Parameterized constructor
layer::layer(intersetionPoint point)
{
    m_start = new layer(&point);
}

// Insert method
void layer::insert (intersetionPoint *value, int place=-1) {
    intersetionPoint *temp = new intersetionPoint(value);

    //Use m_start as reference, if inserting at the beginning
    if (place == 0)
    {
        temp->setNext(m_start);
        m_start = temp;
    }

    //Else, find where to insert
    else
    {
        intersetionPoint *before = m_start;

        //Loop to find the preceeding node
        for (int i = 1; before->getNext() != 0; i++)
        {
            if (i == place)
            {
                break;
            }
            before = before->getNext();
        }

        //Insert after preceeding node and point to the next node
        temp->setNext(before->getNext());
        before->setNext(temp);
    }
}

//Remove function
void layer::remove(int place)
{
    // when removing from the beginning, change start pointer
    if (place == 0)
    {
        m_start = m_start->getNext();
    }

    //Find node to remove
    else
    {
        node *curr = m_start;
        for (int i = 1; curr != 0; i ++)
        {
            if (i == place)
            {
                //Remove the target node
                curr->setNext(curr->getNext()->getNext());
                break;
            }
            curr = curr->getNext();
        }
    }
}

// Print nodes
void layer::display() {
    for (node *current = start; current != 0; current = current->get_next()) {
        //cout << *(static_cast<T*>(current->get_info())) << endl;
        //export gcode function
        //Will print initializations and end commands
        //Also print parameter values

/*
        //Turn off print cooling fan
        std::cout << "M107" << '\n';
        //Set target temperature
        std::cout << "M104" << ' ' << 'S' << "temp" << '\n';
        //Auto-home
        std::cout << "G28" << '\n';
        //Lift nozzle
        G1 Z5 F5000 ; lift nozzle
        //Wait for hotend temp (wait for temp to be reached)
        std::cout << "M109" << ' ' << 'S' << "temp" << '\n';
        //Set units to milimeters
        std::cout << "G21" << '\n';
        //Absolute positioning (use absolute coordinates)
        std::cout << "G90" << '/n';
        //E absolute: E axis is in absolute mode independent of the other axes (absolute distances for extrusion)
        std::cout << "M82" << '\n';
        //Set the current position to the values secified
        //Possibly at the beginning of every interation?
        std::cout << "G92" << ' ' << "E0" << '/n'


        This portion is set aside to represent where the
        intersection point g-code generation will be done or printed
        G92 E0
        G1 Z0.350 F7800.000
        G1 E-2.00000 F2400.00000
        G92 E0
        G1 X65.734 Y75.135 F7800.000
        G1 E2.00000 F2400.00000
        G1 X67.506 Y73.645 E2.07162 F1800.000
        G1 X112.811 Y82.611 E3.90121
        G1 X112.876 Y82.241 E3.91164 F1200.000
        G1 X112.856 Y82.026 E3.91764
        G1 X112.959 Y81.821 E3.92401
        G1 E1.92401 F2400.00000


        //Set the current position to the values secified
        //Possibly at the beginningor end of every interation?
        std::cout << "G92" << ' ' << "E0" << '/n'
        //Turn off temperature
        std::cout << "M104" << ' ' << "S0" << '\n';
        //Home x axis
        std::cout << "G28" << "X0" << '\n';
        //Disable motor
        std::cout << "M84" << '\n';
*/
    }
    cout << endl;
}
