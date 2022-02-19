/* Hello world. dsfasd sdf :-))) asdf :-((  ((( asd fasd f. */

// :-)))))):-
// i      j

// Abc :-))) abc

// abc :-)))):-(((( abc

// :-):- ab
//    ^

// :-:-:-:-:-
 
 import "strings"
 
 func RemoveSmiles(s string) string {
     sb := strings.NewStringBuilder()

     for i := 0; i < len(s); {
         l := i
         skip := false
         
         for s[l] == ":" && l+1 < len(s) {
            l += 1
            
            if s[l] == "-" && l+1 < len(s) {
                l += 1
                
                mouth := s[l]
                
                if mouth != ")" && mouth != "(" {
                    break
                }

                for l + 1 < len(s) && s[l+1] == mouth {
                    l += 1
                }
                
                skip = true
            }
            
            if skip {
                i = l
                skip = false
            }            
         }
         
         if i < len(s) {
            sb.AddString(s[i])
         }
 
         i += 1
     }
     
     return sb.String()
 }
