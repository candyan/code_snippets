' " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " 
 ' S c r i p t   t o   c r e a t e   a   S y s t e m   R e s t o r e   p o i n t   i n   W i n d o w s   7   |   V i s t a   |   X P 
 ' M a y   1 0   2 0 0 8   -   R e v i s e d   o n   J a n   1 0 ,   2 0 0 9 
 ' �   2 0 0 8   R a m e s h   S r i n i v a s a n .   h t t p : / / w w w . w i n h e l p o n l i n e . c o m 
 ' " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " " 
 I f   G e t O S   =   " W i n d o w s   X P "   T h e n 
 	 C r e a t e S R P 
 E n d   I f 
 
 I f   G e t O S   =   " W i n d o w s   V i s t a "   O r   G e t O S   =   " W i n d o w s   7 "   T h e n 
 	 I f   W S c r i p t . A r g u m e n t s . l e n g t h   = 0   T h e n 
     	 	 S e t   o b j S h e l l   =   C r e a t e O b j e c t ( " S h e l l . A p p l i c a t i o n " ) 
 	 	 o b j S h e l l . S h e l l E x e c u t e   " w s c r i p t . e x e " ,   " " " "   &   _ 
     	 	     W S c r i p t . S c r i p t F u l l N a m e   &   " " " "   &   "   u a c " , " " ,   " r u n a s " ,   1 
 	 E l s e 
     	 	 C r e a t e S R P 
     	 E n d   I f 
 E n d   I f 
 
 S u b   C r e a t e S R P 
 	 S e t   S R P   =   g e t o b j e c t ( " w i n m g m t s : \ \ . \ r o o t \ d e f a u l t : S y s t e m r e s t o r e " ) 
 	 s D e s c   =   " D a i l y   R e s t o r e   P o i n t " 
 '   s D e s c   =   I n p u t B o x   ( " E n t e r   a   d e s c r i p t i o n . " ,   " S y s t e m   R e s t o r e   s c r i p t   :   w i n h e l p o n l i n e . c o m " , " M a n u a l   R e s t o r e   P o i n t " ) 
 	 I f   T r i m ( s D e s c )   < >   " "   T h e n 
 	 	 s O u t   =   S R P . c r e a t e r e s t o r e p o i n t   ( s D e s c ,   0 ,   1 0 0 ) 
 	 	 I f   s O u t   < >   0   T h e n 
 	   	 	 W S c r i p t . e c h o   " E r r o r   "   &   s O u t   &   _ 
 	   	 	     " :   U n a b l e   t o   c r e a t e   R e s t o r e   P o i n t . " 
 	 	 E n d   I f 
 	 E n d   I f 
 E n d   S u b 
 
 F u n c t i o n   G e t O S         
         S e t   o b j W M I   =   G e t O b j e c t ( " w i n m g m t s : { i m p e r s o n a t i o n L e v e l = i m p e r s o n a t e } ! \ \ "   &   _ 
         	 " . \ r o o t \ c i m v 2 " ) 
         S e t   c o l O S   =   o b j W M I . E x e c Q u e r y ( " S e l e c t   *   f r o m   W i n 3 2 _ O p e r a t i n g S y s t e m " ) 
         F o r   E a c h   o b j O S   i n   c o l O S 
                 I f   i n s t r ( o b j O S . C a p t i o n ,   " W i n d o w s   7 " )   T h e n 
                 	 G e t O S   =   " W i n d o w s   7 "         
                 E l s e I f   i n s t r ( o b j O S . C a p t i o n ,   " V i s t a " )   T h e n 
                 	 G e t O S   =   " W i n d o w s   V i s t a " 
                 e l s e I f   i n s t r ( o b j O S . C a p t i o n ,   " W i n d o w s   X P " )   T h e n 
             	 	 G e t O S   =   " W i n d o w s   X P " 
                 E n d   I f 
 	 N e x t 
 E n d   F u n c t i o n 
 