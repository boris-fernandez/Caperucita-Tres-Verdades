#include "pch.h"
#include "Escena1.h"
#include <iostream>

using namespace System;

void Escena1()
{
    Console::Clear();

    // ----ASCII ART DE FONDO(el bosque) ----
    Console::ForegroundColor = ConsoleColor::Red;
    Console::WriteLine(R"ASCIIART(
                                                                                            .::.                                                        
                :                                                                        .:.    .:                                                      
               ; .:                                                                    ::         .::                                                   
              :.   :                                                                 ;.              .:.                                                
             ..      ;                                  .                            ..:+;;      ;+;;.:                                                 
             :         ;                :.             :..             .      .      .::+;+      +x:;.:                                                 
   ..      ..            :.      ::     :..     .     ;   :   :.. .:. :..    : ..: ; ..     ;  .     .: ..:  ..: ..: ...  ::  .      .          +       
   ...    ..               .:    ...   :  :.   ...   ;     :.;  .:.  +  ..  +   +; : ..     ;  .     .: :  ;:.: ;.  ;.:..:  :... ;  ..:        : :     .
  .. :.   :                .  +.:  ..  :    :  :  ..;        :.   : ;    .::. .::;;: .;;;+x+;+xx;;;;;;.  +x   .::   :: :.   :  .: :..  :   :.:.   .   : 
  :   .:..                ..:  :     :;      :;    :          .:: .::     :.  ;.     .::  .::            ;:    ;.  .:   .: ;.   .+ :    : :  ..    ...  
 :     ;  ..             ..  +;.     ;        .; .:..        .::;:;:.:;:::::       ::   .:              ::.....;;;;       ;:   ..  ..    ;    :.    .   
;      ..::.            ..    :....  .::      ;    .:            .:.  ::.        :.    :.                   ::::.          .:.:      . .;      .:       
;         :            ..      .:::   ;        :..:          .::...              :     :.                   :;::.            .;.    ::..:.       ;.     
 :       :            :.         :   ;          :;:::::::..;                     :.     :                      :.          .;...     ::  :.      :.    :
  :    .:            :            ..;:;        ;::      :   :                     ;      :                  .:.              ::     ..    ..       :. : 
   :  :.           ..               :.:         :       :   +       .;;;:         ;       ;              .;.                   .;  :.      .:     :.::  
    :    .:       :                  ::          .:               ;;;;;;;;.      :         ;            .;;;;;;;;::....       ..::;          :     ::   
     :  .:      ;.                     :.          ;            .;;;;;;;;;;.   ::          ;                        :   :      : ;;+       ;+;.   ..    
;     :;.     ;.   :;.             ;+;;;+;;;;x.                 ;;;;;;;;;;:: ::           ;                        ..   :.     :  ;         :.   :      
 ;      ;         .+.                ;    .  :                   ;;;;;;;;;++.            .:                        ;     ;      .;           :.; ::;:  .
  :   .:+;:::::. +:                    :. .:::.                    ;;;;;;;              :.                                     :              .+   .. :.
  .: ..        ::                        .:.                      ;;;;;;;;;            :.                                    .:                 ; :  :  
   ..  :.   .:                              ::                   :;;;;;;;;;:         ::                                .       .;:            :  :  :   
    ..  .:;;.  .........::.....+............                    ;;;;;;;;;;. ..     .;                                 :.;      :               :+ .:    
     .:   ..             :     ;                               :;;;;;;;;.         :.                                 :.  :.  .:                  +.     
       ;    :.           :     :.                            ;.     + .:        .:                                 .:     .:::                 .:       
        ;     ;          :      :                          ;.      ;.  :       :.                                .;         ::     ..;::..;  .;.        
         :;;;.          :        :                       ;.       ;:   .::    :.                               ::             ::     ..   : .:          
          ..               .:.                         ;.                    :.                                  .;.        .;;;+.   :.   ;:.           
           :.                                        +                      .:                                  ;:            ::     .;:.:+             
           ::                                     .;                        +                                ::                  ;:      +              
        ;                                        :.                        ;                               ;.                      .;.        :         
         :.                                    ::                          ;                                        .;;::::+::::.           ..          
          .:                                  ;                           :.                                         ..    ;               :.           
            :                               .:                            ;                                          :.    :             .:             
             .:                            :.                            :.                                           .....            .:               
               ;                          :.                             :                                                            :.                
                :                        ..                             :.                                                          :.                  
             :;:                         :                             .:                                                          ;                    
.::;;;;;:.                              ..                             ..                                                        ;.                     
    :                                  .:                              :                                                        ;                       
    :.                                 ;                               :                                                          ;:                    
     :                                ;                                :                                                              :;;:.             
     :                              .:                                 :                                                                          .;+:::
::::                               :.                                  .:                                                                          .    
)ASCIIART");
    Console::ResetColor();
    Console::WriteLine();

    // ---- MEMORIA DE CAPERUCITA ----
    Console::ForegroundColor = ConsoleColor::Red;
    Console::WriteLine("> MEMORIA DE CAPERUCITA:");
    Console::ForegroundColor = ConsoleColor::Gray;
    Console::WriteLine("  \"Tengo que entregar esta canasta en la casa de la abuela.");
    Console::WriteLine("   Pero... estas huellas en la tierra no son mias ni de los animales del bosque.");
    Console::WriteLine("   Siento que alguien me esta observando desde la espesura...\"");
    Console::WriteLine();

    // ---- OBJETIVO DEL NIVEL ----
    Console::ForegroundColor = ConsoleColor::Yellow;
    Console::WriteLine("> OBJETIVO DEL NIVEL:");
    Console::ForegroundColor = ConsoleColor::Gray;
    Console::WriteLine("  Cruza el bosque, esquiva las trampas del camino y evita al Lobo a toda costa.");
    Console::WriteLine();

    // ---- PROMPT DE CONTINUAR ----
    Console::ForegroundColor = ConsoleColor::DarkGray;
    Console::WriteLine("[ Presiona cualquier tecla para continuar... ]");
    Console::ResetColor();

    Console::ReadKey(true);
    Console::Clear();
}