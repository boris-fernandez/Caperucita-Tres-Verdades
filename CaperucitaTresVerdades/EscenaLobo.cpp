#include "pch.h"
#include "EscenaLobo.h"
#include <iostream>

using namespace System;

// Escena de aviso: se dispara al pisar una huella de lobo en el nivel.
void EscenaLobo()
{
    Console::Clear();

    Console::ForegroundColor = ConsoleColor::Gray;
    Console::WriteLine(R"ASCIIART(

                               .:::..   :+;.     .::::::.                                                .:+;::::::::.                         
                          ::....;;:..:x::                                                                 ...++;;::. .:::                      
                       .;. .:::.  :x:; .:                            .$X.                                 .: :::X;;+++;:..:.                   
                      :;. .  ..;+;.  ; :.                            :+.x:                                 ...:. ;+;.  .. .:.                  
                     ;.:;::;+:. .:. ..:.                            .;...X.                                 .:....;..;+:... ::.                
                   .:. .::::... .:.:::                               .::;x.                                      :..  :: .:;;::::.             
                  .:........:....:.                .               :++. .;+;.               ...                   .::.....::::.                
                 ..::::.  ... .                   :X+            .;+       .+;.             :Xx:                                               
                                                 :+.$:          :x:  ::;;;;. .+:           .+;:+.                                              
                                                 +;..+         .x: :;.     ::.:+.          .x;:x:                   .:.                        
                                                 ;X+++:.       :+..;         ..+;.      .;+++x++.                .;:...::.                     
                                                 .;x;..:::;.   :+;;.          .+x.   .;;:.   .x;.               .: . .;+::                     
                                                 ;X:      .;$:  xx:           :++. .++.       .X;                .:::.:::.                     
         ::;++;                                 .x;  +++++.  .;:.x+.          :X; +:  .+;...:;.+x.                  ..                         
      .+.  :+;.:.                               :X::;     .+: .;;.X+         .+x.X. .+:      :;+$.                                             
    .;.  ..  ..x;                               :X+:         ;:.x;.X:       .;+.X::..         :xX.                                             
   .::::.:.   . ::    .                          x+;.          .:X: x+:::::xx. +;;.          .:$:                        .:::::::. .... .:::.  
   .:.. .:;..:::   .:: .:                  .     .X+.          ..:x.  .;;.    .x;.          .:x;    .;x:                  .::;;....:. .;.  ..:.
      .::::.       .::...                 .X+      ;x:.          +x.           ;x.         :++.    .+:;:                   .... .:+++::.:: .:. 
                                          ;;:X.      ;x+;:.    .+x.             :x;::.:;++X;.  ::;;;x++:                     :......   :++;:::.
                                          .+:+;.;;::.   .;xxxxx+:.     .:;;;;;;:. :;++;.    .;;:. .+x;:.                       .::  .:::  ..;;;
                                           :;:;;..:;+++;:.           .;;.      .:::.       .+:.:;: .;+                           .....  ..:.   
                   ..                       .X  .:;:::. .;+;        .x.  .;::..   .;;;:.   ...   .;:;+                              ....::.....
                .:;:.:.                      $ .;.     .::..:x:     X. :;:       ......:. .:::++;. :::                                         
                :::::.                       X;::        ..;..++    X.::.           .:;;::::.   .:X:                                           
                                             .$::           .;:x:  .x.:.                ......:....+;                                          
                                              :X:.           .:X:  xx.;                          +;:x:                                         
                                               :x;.          .;x.  $ .;                          ;+.;+                                         
                                                .+X:..      .X;   x: ::                           ;:$;                                         
                                                   .+X&$$$$x:   .x: ::                            .X+                             ..::.        
           ..                                                   +: ;:                       ...:+$$;                           .::;:..:+.      
           .:.                                                 :+:::                    :xX$Xx;::.                            .:..:;:..:.      
            .::.                                               .x:;.                .:;XX;                                     .::.:::.        
              .+;:....:.......                                  ;x;.           .+xXXXx;.                            ...                        
               :.;;.   .::.  ::.                                 :x+;.       .+x:.                              .::;..:.:.                     
               ; .;;x;:..      ....                               .+xx+;;;:;xX+.                            .::;;:.      .:.                   
               : ::  ;;+::;;;;::..:.                                 .:;+++;:                             .:::..         ;;:                   
                :.:. .; :+++:     ...                                                                    .:..          :++::                   
                ....  ;  :: .:++..:.:.                                                                  :.        ;+;...;x:                    
                 .::.  . .:.   ;.;;. :.          .::::                                                 ..  .   . .       ;.                    
                    .:    .:.  .:. .:.:.       ..:.   .:                                                :.          .:;.                       
                      . .:...::..:::::.:.      ..::. . ..                                                    .::::::.        ::. ..            

)ASCIIART");

    Console::ResetColor();
    Console::WriteLine();

    Console::ForegroundColor = ConsoleColor::Red;
    Console::WriteLine("> Caperucita encuentra huellas frescas en el barro...");
    Console::ForegroundColor = ConsoleColor::Gray;
    Console::WriteLine("  \"El lobo anda cerca. Tengo que esconderme antes de que me vea.\"");
    Console::WriteLine();

    Console::ForegroundColor = ConsoleColor::Yellow;
    Console::WriteLine("> El lobo viene por el camino.");
    Console::ForegroundColor = ConsoleColor::Gray;
    Console::WriteLine("  Busca una roca cerca y presiona S para esconderte antes de que llegue.");
    Console::WriteLine();

    Console::ForegroundColor = ConsoleColor::DarkGray;
    Console::WriteLine("[ Presiona cualquier tecla para continuar... ]");
    Console::ResetColor();

    Console::ReadKey(true);
    Console::Clear();
}
