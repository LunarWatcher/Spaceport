#include<iostream>

#include "core/Spaceport.hpp"

int main() {
    try {
        spaceport::Spaceport::init();
    } catch (int err) {
        return err;
    }
}
