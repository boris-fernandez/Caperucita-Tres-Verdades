#include "pch.h"
#include "Escena2.h"
#include <iostream>

using namespace System;

void Escena2()
{
    Console::Clear();

    // ---- ASCII ART DE FONDO ----
    Console::ForegroundColor = ConsoleColor::Gray;
    Console::WriteLine(R"ASCIIART(
                                                                                                                                                                
                                                                                                                                                                
                                                                                                                                                           +.   
    .*:                                                                                                                                                   ::-   
    -.:     .#.                                                                                                                                   *=     .: .:  
   :: .:    = =     +:                                                                                                                           -.-     :.  -. 
   @+  :.  =   +   :::         :                                                                                               +:     .#         =  +   ::    + 
  +=.- -= ==   -+ .: .::      +-          :+               .                  ::::                              =.   :+       ::-     + -       +    =  ==   .+-
  +  :..: .-   :: =: .#*:    :. -  :+     = -    -     =  +-               .::     :=-::                       :::   -.: #.  .- .:   =  -   =: -=    == :.    = 
 =    : ---     :::   - =    -  :..:.:   +  .::-:-:   +:: :..        -   .:   .:     -. -.  :         =- ++   .- :: -  -* =  -   -. .=   = :-:  +    = ::      =
::    .-=##=    +%-  -.  +  +-  -+=. -:  #  -*:-= -  =  =+::= -= =+ :-- -:  -:        .: ::++   : :+ :.-=..-  *  .+:+. *.  =:+.  == *    :*- .:=.     **-      +
=      :=+*=:    =: ::    = =   .=##.:: -.   +: - -- %:%**  :=.:*-.*= -=   :    --:       :: + .-+-:-=.-@  :. =  :-=:  *:  *=:  :.- =:   =*   ==      -%       .
        +#. +    -+::     .%:    =+.- +.*.  .+- :: *=:+ *+  =+  +. @. .+     :==::=-      +  .*+ =  =- =.= -+-  :*+#:  +   =+  -+:=+=    ::    +      +--       
        :-   *   .+-       :+    =: :::+:   = ::=- -##  :%  -=  == *   -     +::::::=. :  =  .#::.   :+. .: +* .- +*  +:   .+..: =**    .-      =    :: :.      
+      =*     +   -*+:    *+-   .-   = *-  =   :.- -%.   -- :.  .:+:   .+:  --::::::-- .:=    :-=+  .#=   -.:: -  .*- -=   .+.:.  +*    =        =   =  .-      
       -.     :=:::+-      *    -     *=  -.    -+---    .=+=    *%    .#-  =-::::::--  +#    -#=   .:     +.=-:   -+:-     :+-    +   *..      .-= *    ::     
      :-       =  .-        +  -       #:+:     .==-*    :=-:    --     .- :+=-------+: =.     *    -+.   .=*:-     -+      .=     .-  .:=      =..+      -.    
      -         +.-          +-.        #*-.    -+#@:     ++      +==++:::.+=.......:====::--:+%:   .:     +:-       =      =       -.  =       .--:       -    
     -.          #:         :=:         .++     -.=:       -.     *::-=   -.          ::   =::::    :      .@::     .-#    -         +:+         ==        .:   
    ::           .*.        *-           .-      +*+      :*=      +     -.            :.  --+:    :         *.     ::    =.          #          +          -=::
   :-             :-        *-+-       ==:+.      *.       ::      :+   :.              ::   ::::-#+-       #.       -   -.            +        +            =. 
  .-               ::         +         *.        .+        =+-+.      -                 ::       +-       =.         + .*:-=       .#*-+      =              + 
 .=                 ::       =.          *        ++=.......-%==      =                   .-     .+       =.           +   -.        ++       -.               *
 #.::-.          -:--**--=::*.            +        +  * +     ::     =                      =    =       =-:          . * =.          +      -:                 
 .   -           ::   =  = =.              =        + = =          .=         .  ..          +   :::::+-:%+%          +-:*.            +    -:                  
    -.            :.  -  ++.               .=        #+-+         :-         -++-%%.          =       -  *+            ++.              +  .=-::#.           *-:
::-+.              -. :  %.                 :*++:::::-           -:          ==---=+-          -.     -  +             =.                =     -:             = 
  -:                -..:%=-==             *==+#:                =.          :+------=*+:        ::     =+             =.                 :%=:*%-               +
 -:                  -     +               *= ::               =           ++=---------=++===-:  .-   .*-::.......   ++===             =::-- +=                .
=:                    -  .=                 +-=:              -              .=+---------------+= .-          .+ --.....%              .=.+.--                  
:                      =--                   -              .-                 %++--------------=* .-          =  :    +                .*-.-                   
                        *                     -            .-                   +#------=-----+*-=. .-         =  :   +                  :@=                    
                         +                     -          .-                     =+-++--*=----##-=+   -       .*::=  =                    =                     
-#                  :*=:-=#                    .-        .:                      .*-+%*+*=---+#%--+-   =           .-                    +                      
*                    :+---=-:::::++::#-::::::::::       ::                      :*=+*+= -=--+#+#=--=+:  =.        .-                    +                       
                      :-         :.  =                 =.                       %=- -*=  -+-* :*##=--++: =.       ==:::::::::-=::---::-%=*##%:                  
                       :-        :   =                =                         #-+:*=-   -++=  *=*==-:   :-                 .-  ::        -.                   
                        .=       :   =               *                           - :-:     *++  =+-        .-                .-  .:       -.                    
                          +     .:   -.             =                                    :*++  -#+:          =               .-   -      -.                     
                           *     ::::-            .-                                     ---                  =              ::   =     =.                      
                            +                    ::                                                            -             -:   =    +                        
                             =                  -:                                                              -.            ....    +                         
....::::::::------::-----::::-*                -.                                                                -.                  #                          
        -.    =                               -.                                                                  -.                +                           
        -.    ::                             -.                                                                    -:              %---:::::---:::::---::---::::
        -.     =                            -                                                                       ::                              =     -.    
        -.     +                           =                                                                         .-                             +     -.    
        -.     +                          =                                                                            +                            +     -.    
)ASCIIART");
    Console::ResetColor();
    Console::WriteLine();

    // ---- MEMORIA DE CAPERUCITA ----
    Console::ForegroundColor = ConsoleColor::Red;
    Console::WriteLine("> MEMORIA DEL LOBO");
    Console::ForegroundColor = ConsoleColor::Gray;
    Console::WriteLine("  \"Siento pasos pesados a mis espaldas y el eco de los disparos retumbando en el bosque");
    Console::WriteLine("  \"El Cazador me está rastreando sin descanso.");
    Console::WriteLine("   Tengo que llegar a mi guarida antes de que me alcance...");
    Console::WriteLine("   Debo usar mi olfato para orientarme entre los peligros y evitar sus trampas.\"");
    Console::WriteLine();

    // ---- OBJETIVO DEL NIVEL ----
    Console::ForegroundColor = ConsoleColor::Yellow;
    Console::WriteLine("> OBJETIVO DEL NIVEL:");
    Console::ForegroundColor = ConsoleColor::Gray;
    Console::WriteLine("  Huye del Cazador, esquiva los obstaculos y usa tu olfato para encontrar el camino a la cueva.");
    Console::WriteLine();

    // ---- PROMPT DE CONTINUAR ----
    Console::ForegroundColor = ConsoleColor::DarkGray;
    Console::WriteLine("[ Presiona cualquier tecla para continuar... ]");
    Console::ResetColor();

    Console::ReadKey(true);
    Console::Clear();
}