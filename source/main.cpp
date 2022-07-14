#include <engine.hh>


int main(int argc, char* argv[])
{
    Engine engine{ "Astro" };
    const bool b_success = engine.initialize();

    if (b_success == true)
        engine.run_loop();

    engine.shutdown();

    return EXIT_SUCCESS;
}
