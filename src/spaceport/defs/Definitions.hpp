#pragma once

// Define the app type, because crow is weird and I'd rather not have to manually
// update numerous instances if I ever change this.
// I can and probably should add any imports for future middlewares here though. Or just forward
// declarations. We'll see.
#define CROWAPP crow::Crow<>
