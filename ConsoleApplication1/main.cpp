
#include <iostream>
#include "Common.h"
#include "Downloader.h"
#include <synchapi.h>

int main(int argc, const char* argv[])
{
    try
    {
        Downloader::instance()->setCompletedCallback([](int) {
            cout << "All Done!" << endl;
            exit(0);
            });
        Downloader::instance()->download("https://i.pinimg.com/564x/08/f8/cc/08f8cc95bb0a360fd9c1e8c01b8224d5.jpg", "./");
        Downloader::instance()->download("https://i.pinimg.com/564x/da/cd/8a/dacd8a1a18d817e79f4b140523547e95.jpg", "./");
        Downloader::instance()->download("https://i.pinimg.com/564x/92/54/70/9254701fdd4e2d370b86b5f7c29e638e.jpg", "./");
        Downloader::instance()->download("https://scontent.fsgn5-2.fna.fbcdn.net/v/t39.30808-6/340224613_757633572624228_8248779285831291247_n.jpg?_nc_cat=1&ccb=1-7&_nc_sid=730e14&_nc_ohc=ul8Y90xCzvwAX-FACe5&_nc_ht=scontent.fsgn5-2.fna&oh=00_AfBfaEFWyCu2E7EF2Mp1MJ7a5IGL68TRrj7kjYGLO_tGhQ&oe=643647C2", "./","fb.jpg");
        Downloader::instance()->download("https://i.pinimg.com/564x/04/39/92/043992188981c4ee85f88e0416f9d279.jpg", "./");
        Downloader::instance()->download("https://cdn.fbsbx.com/v/t59.2708-21/329046913_1140628763313840_8397976470219686676_n.docx/Project-java.docx?_nc_cat=101&ccb=1-7&_nc_sid=0cab14&_nc_ohc=7litEyaoOOEAX_29hx2&_nc_ht=cdn.fbsbx.com&oh=03_AdT4VG8coropmwri94k1YUH5VTMw6_rNteTEiRPaMiPaTg&oe=6432DB35&dl=1", "./","java.doc", [](int no)
            {
                cout << "Downloaded: #" << no << endl;
            });



        Sleep(1000);

        return 0;
    }
    catch (const exception&)
    {
        cout << "aaaaa";
    }

}

