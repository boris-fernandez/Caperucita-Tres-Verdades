#include "pch.h"
#include "SelectorNiveles.h"

#include <iostream>
#include <conio.h>
#include <vector>
#include <string>

using namespace System;
using namespace std;

string completarEspacios(string texto, int ancho)
{
    if (texto.length() < ancho)
        texto += string(ancho - texto.length(), ' ');

    return texto;
}

void mostrarPersonajes()
{
    vector<string> caperuza =
    {
        "",
        "",
        "",
        "",
        "",
        "                         X&&$",
        "                       &X    :&:",
        "                     $$        x&",
        "                    &; :&&$$&&;  &",
        "                   &; &;      :& :&",
        "                  +& &x        :& X&",
        "                  &: &;         &  &",
        "                  &x .&        &; ;&",
        "                   ;&+.&&+:.;&&:;&x",
        "                     &&        x&.",
        "                   &x     &&     +&",
        "                  &;     ;&$+      &:",
        "                 &&      &  &:     +&",
        "                 :&;X&&&X    ;&&&&+&$",
        "                 &  ;&+        .&&  &:",
        "                &. ;&&.         &&x  &",
        "               &$ .&x&          x$&x +&",
        "               &x&& &.           & &&$&&&",
        "                +: +&            X&&    .&&",
        "                   &              &&&&+   &.",
        "                  x$              x&      &",
        "                  &                &&&$&&&.",
        "                 $&$.            .x&&",
        "                     .&&&&&&&&&&;",
        "                      $+ X$:$ :&",
        "                      +& $x.& xX",
        "                      +& &+ & $X",
        "                     x&&&&  &&&&&"
    };

    vector<string> cazador =
    {
        "",
        "            .$&&&&X",
        "          $&        &$",
        "         :&          &:",
        "      $&&$$XXXxxx++++&x",
        "         X&          &x    &&x",
        "         .&          &   +&+&",
        "          .&:       &:  &+&X",
        "           :&&&&&&&&. ;&.&:",
        "        &&:         $&&&&",
        "      X&           ;&   $&",
        "      &           :&     &:",
        "     +X          ;&      +$",
        "     &;  :      +&    ;   &",
        "     &   &     &x     &.  &.",
        "    +&  ;&   ;&.      &x  $X",
        "    &x  && .&;        &&  ;&",
        "    &.  &&&x          &&  .&",
        "    &  ;&&.           &&:  &",
        "    &;+&&&&$$Xxxxxxx+X&$&++&",
        "    &&&&.&.          .& &&&$",
        "    .&.  &     xx     &",
        "  $&   :&     &&.    &",
        "+&+ ;&&    :&&;    &",
        "  && &    +$&x    &",
        "      &    xX$X    &:",
        "      &    Xx.&    &+",
        "         &&&&&&  &&&&&&",
        "         &;   &  &.  :&",
        "         &+   &  $:  ;&",
        "         &+   &  $;  +&",
        "       .&$    &  X+   X&:",
        "      .&&&&&&&X  ;&&&&&&&:"
    };

    vector<string> lobo =
    {
        "",
        "",
        "",
        "           .            :",
        "          &&&.        ;&&X",
        "          &  +&      &+  &",
        "         .&    $x;:xx    &",
        "          &              &",
        "         :&              &.",
        "        ;&                &",
        "       +&+    X&    &x    x&;",
        "        $$                &x",
        "        +&+&&.        :&&+&:",
        "        &:   +&      &+   ;&",
        "       Xx     +&    &:     &x",
        "       &.      .$&&$       x&",
        "       &                   :&&",
        "       &:                  X&+&",
        "       x&X                &&. &:",
        "       :&&                &   :&",
        "        &X&              &x    &",
        "        $+&x            ;&     &",
        "       .& &   :&+X&:   &XX      &&",
        "      &+&;  .&  &.  ;&Xx&&     $&",
        "     ;&XX  ;&  &:  &x&   X&&+   x&.",
        "      +&;&  ;&  &;  &.&.",
        "      X$.&  ;&  &;  & $+",
        "         &  &  :&  &: :& :&",
        "        ;&  &:  &  &. :&  &.",
        "       &+   &   &  &  :&   x&",
        "        ;XXX&  ;&  &; .&+XXx",
        "          :&   $&  $x  .&:",
        "          &&&&&&    &&$&&&"
    };

    int maximo = caperuza.size();

    if (lobo.size() > maximo)
        maximo = lobo.size();

    if (cazador.size() > maximo)
        maximo = cazador.size();

    for (int i = 0; i < maximo; i++)
    {
        string lineaCaperuza = "";
        string lineaLobo = "";
        string lineaCazador = "";

        if (i < caperuza.size())
            lineaCaperuza = caperuza[i];

        if (i < lobo.size())
            lineaLobo = lobo[i];

        if (i < cazador.size())
            lineaCazador = cazador[i];

        lineaCaperuza = completarEspacios(lineaCaperuza, 40);
        lineaLobo = completarEspacios(lineaLobo, 40);

        Console::ForegroundColor = ConsoleColor::Red;
        cout << lineaCaperuza;

        Console::ForegroundColor = ConsoleColor::Gray;
        cout << lineaLobo;

        Console::ForegroundColor = ConsoleColor::Yellow;
        cout << lineaCazador << endl;
    }

    Console::ForegroundColor = ConsoleColor::White;
}

int SelectorNiveles()
{
    int opcion = 0;

    // Una sola presentacion por visita; las teclas invalidas no redibujan el arte.
    {
        Console::Clear();

        Console::ForegroundColor = ConsoleColor::White;

        Console::WriteLine(R"ASCIIART(
                       _             ____                                 _ _          ____       _
                      | |    __ _   / ___|__ _ _ __   ___ _ __ _   _  ___(_) |_ __ _  |  _ \ ___ (_) __ _ _
                      | |   / _` | | |   / _` | '_ \ / _ \ '__| | | |/ __| | __/ _` | | |_) / _ \| |/ _` (_)
                      | |__| (_| | | |__| (_| | |_) |  __/ |  | |_| | (__| | || (_| | |  _ < (_) | | (_| |_
                      |_____\__,_|  \____\__,_| .__/ \___|_|   \__,_|\___|_|\__\__,_| |_| \_\___// |\__,_(_)
                                              |_|                                              |__/
 _                _                                     _           _                 _      _   _
| |    __ _ ___  | |_ _ __ ___  ___  __   _____ _ __ __| | __ _  __| | ___  ___    __| | ___| | | |__   ___  ___  __ _ _   _  ___
| |   / _` / __| | __| '__/ _ \/ __| \ \ / / _ \ '__/ _` |/ _` |/ _` |/ _ \/ __|  / _` |/ _ \ | | '_ \ / _ \/ __|/ _` | | | |/ _ \
| |__| (_| \__ \ | |_| | |  __/\__ \  \ V /  __/ | | (_| | (_| | (_| |  __/\__ \ | (_| |  __/ | | |_) | (_) \__ \ (_| | |_| |  __/
|_____\__,_|___/  \__|_|  \___||___/   \_/ \___|_|  \__,_|\__,_|\__,_|\___||___/  \__,_|\___|_| |_.__/ \___/|___/\__, |\__,_|\___|
                                                                                                                    |_|
)ASCIIART");

        cout << "\n\n";

        mostrarPersonajes();

        cout << "\n\n";
        cout << "[1] Nivel 1: El sendero de las huellas\n\n";
        cout << "[2] Nivel 2: Huellas en la Oscuridad\n\n";
        cout << "[3] Nivel 3: La verdad entre las huellas\n\n";
        cout << "[4] Salir\n\n";
        cout << "Selecciona un nivel: ";

        while (opcion == 0)
        {
            const int tecla = _getch();
            if (tecla == 0 || tecla == 224)
            {
                _getch();
                continue;
            }
            if (tecla >= '1' && tecla <= '4')
            {
                opcion = tecla - '0';
            }
        }
    }

    return opcion;
}
