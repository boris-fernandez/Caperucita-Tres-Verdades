#include "pch.h"
#include "Escena3.h"
#include <iostream>

using namespace System;

void Escena3()
{
    Console::Clear();

    // ---- ASCII ART DE FONDO ----
    Console::ForegroundColor = ConsoleColor::DarkYellow;
    Console::WriteLine(R"ASCIIART(
                                                                                                                                                                
                                                                                                                                                                
                                                                                                                                                    $$          
   +&                 X                                                                                                       :                    :::         X
   : ;               ;:;                     ;.                            xXxx;.                                            $;       X+           +  $       . 
  &  ;     &+        ; ;                .    $x                          &         $&&&X                                    .. +     :  :  &x     +    $      X 
 x    ;   ; .       $   ;      Xx      ;X   ; :                      x;:            &    ;;                    $:   &       +  .;    x  x ; ;    .;    ..    $  
 :    ;.  ;  X     +    :: :$ .  :     + $  ;  X        ;    $      &       ;        ++   +    .              ..;  + x     ;    ;   &    &+  $   +      x   .:  
$      + X    x    $+   $X &..X  x    X   ;::  .+  +&   :X  ..;    x    &.              ;  +x  +X         &   x  : + :.   .;     ;  ;;  .&    x $&&    x&&  +   
 :    X x$X   &;   ;     X+  X    &  ;    x +  $   + X ; .  +  . x.    $                $     x  :   .&  & & +:  x&   $   :&.   xX  X   ;.    :  +      x  &$$  
$      x &X&  :   x      ++   x  ..  ...&.:X    & &  ;;+  ;+   x$     &       ;&x             x  X   X xx   : :  $&    $  .:     ; ;    &&:   &&:     X  $  :   
        X& .+  X :$;     $x    .  ;  x $ x.$     &    &+  $.    x          X$:  .&           X    & &  :+   ++   x +  .+; +    x& $x     X    ;X.    ;;X  ; +   
       .&   +  Xx $     X  &  :&  ;X&:$   x&    X:     X  X&   .&.        X       ++        XX    x&&  &     &  X  ;.  X &+   + .xXX    x      $X    X ;.x$&    
       .;    &  xx     ;.   + ..   ;xx    :&    &&    &&. +     .        $.         &   X    +    $+  &       xx    &   ; ;  ;:  X&    +        &   &   X &     
&      $     .x  $     X    +  x   +.X     xX    :    .;  ;      x  .    &           &   $  +      $ +&&    .&&+     x   &   x    &+   .&     .X.  +    .$.&    
      $       +  +    $      &  X  X&       +   $      :.&.      +&x    X:           &    +&        X .;     &$       ; +   +     .X;  ..      ;:  x     ;&     
     ::        $x    +        $:&X x         & &        $..      $ +   :x            &    X.X      +x&:      &        .; $ $       x   x        :.&       x     
     X          &   x.        ..: .;;$     ;X:x:$      .&.        X:   .x            x    :&        &X      +          :. $.        & +          &         &   :
$   &           .; ::          +.x  &       +  X        X          ;   +X::::::::::::++   +         &      .+ X      :;:+ +          &          .;         .+   
 ; x             X x .:      :: +.&x         &;          x  + ;.          +&&.  &&       &         X:x       &        $  &           ::         &           x   
 .&;              &  x        X  +X           $          ;x + :.      Xx.   xx                :. ;  &       +          x$             x.       $             &  
 ;+                x&          + x            .:         &  + ;.     $      &                 :. ; +       +.          &. :         :  $      x               $ 
&x                  &           &:::         X..x         ;           &.       ;&&+           .. ;X       x              &x         +:       $.                &
&                    X           +&           X            X            .Xxx.        :xxx+       Xx;;;;;:;:              &           +      ;.                 :
&&&&&            &&&&&;          +.            +            x      ;:.+       x&;          .&.          :X x.           &             &     x                   
   &             ;;               ;:            &  X.+           .;:::X           &           X         x x            X               $   $   :;               
  ;;              +X            $x+&             ; + +      :+;;::::::+;          x:          ::        $;:           &                 ;      $             &+X
 +;                x             +               .$; x    x:::::::::;;         X&            :&         &.           +                  ;;    ;.              & 
.+                  &             &   ++ :x       ;x;X    ::x::x::x:X    +$X;              $x          .:           &                    ::  ;+               ::
$                    X             +  ;   ;              :;:$::++XX;&$;                .X&            ;X           X+;x&              :+. X :;                 x
                      &             X X   ;            ;;:xX&&:. .X :              +&X                          $  ;  &                x    X                   
                       $             x&   :          +$x;.+  :;  :xx+        ;$X+.               :$;+X          +  ; +                  X  $                    
                        +            :&$$$:      x&;      .+  ++        +&$                      +    x        ..  +&                    &x                     
                        .& ;;                ;&:                   ;&x               x           x$&$&x        +   x                     &                      
.                        .; ;              &;                   :$.                  $&&;        $+xxX$        X+;$                     X                       
                     x :&&&:x            &.                    &                        &$&;    .$     x&;       X                     &                        
                      &:.   x           &                      .&                          &:&&x  ;x      x:    x                     $    ;                    
                       &.   x           +                        :$x                        &&&     &       X   XXXxxxxxxxxx$xx+xX+++&&&&x&:                    
                        &&&&x           &                             &&;                   +&:      +:  x.  &              ;    ;       .;                     
                         &               &                                 .x&&:            +&         & .&  .+             +    ;      +;                      
                          x               ;&                                      X&x+.     +  :&       x + :&              x    ;     ::                       
                           &                 &X                                          &&+ && &        &&&                X    ;    :+                        
                            x                   x&:                                           ;x&         x  +X             x    +   ::                         
                             &                      &&:                                         &         &&  &             $+;;;+  .x                          
                              $                          &&                                     &         & +&                     ;:                           
++;;;;;+x;;;;x$;;;;++++++++xxxx                             ;XX                                 & ;xxxxx;&  .x$:                   +                            
        :     X                                                 &:                              &        &       &;              :x                             
       ..     $                                                   &:                            &    &   &          $$           &$$XXXxxx+++;;;:::....         
       ..     $                                                    X                           .x   &x   &            :$.                         &     $       
       :.     X                                                    .X                          ;:  +:$  :;               &:                       &     X       
       ;      x                                                    X                           .+  x &   $                 &                      &     x       
       x      +                                                   x;                            &  x x   $                  X                     &     ;:      

)ASCIIART");
    Console::ResetColor();
    Console::WriteLine();

    // ---- MEMORIA DEL CAZADOR ----
    Console::ForegroundColor = ConsoleColor::Red;
    Console::WriteLine("> MEMORIA DEL CAZADOR:");
    Console::ForegroundColor = ConsoleColor::Gray;
    Console::WriteLine("  \"El rastro me conduce al corazon del bosque.");
    Console::WriteLine("   Veo las huellas del Lobo mezclarse con los pasos de Caperucita...");
    Console::WriteLine("   Algo no encaja en esta escena. Debo examinar las pistas con cuidado,");
    Console::WriteLine("   desactivar mis propias trampas y descubrir la verdad de lo que ocurrio.\"");
    Console::WriteLine();

    // ---- OBJETIVO DEL NIVEL ----
    Console::ForegroundColor = ConsoleColor::Yellow;
    Console::WriteLine("> OBJETIVO DEL NIVEL:");
    Console::ForegroundColor = ConsoleColor::Gray;
    Console::WriteLine("  Avanza por el camino, reune las pistas clave, desactiva tus trampas y revela el verdadero misterio.");
    Console::WriteLine();

    // ---- PROMPT DE CONTINUAR ----
    Console::ForegroundColor = ConsoleColor::DarkGray;
    Console::WriteLine("[ Presiona cualquier tecla para continuar... ]");
    Console::ResetColor();

    Console::ReadKey(true);
    Console::Clear();
}