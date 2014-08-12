��    8      �  O   �      �    �  �  �  c  k     �	  (   �	  h  
    m     v     �  	   �  	   �     �  
   �  
   �  !   �     �     
                1  5   K  $   �  +   �  +   �  )   �     (      F  %   g     �     �     �  F   �       +        F     \     c     i     p  	   v     �     �  #   �  *   �     �     �  %   �      #     D     V  $   h     �     �      �     �  �  �  �  �  �  +  �  �     �  4     B  I  �  �&     ,+     F+     `+     u+  -   �+     �+     �+  =   �+  g   ,,  +   �,  
   �,     �,  �   �,  T   r-  C   �-  J   .  J   V.  H   �.  +   �.  .   /  G   E/  :   �/  >   �/     0  �   0     �0  i   �0     ,1     E1     T1     a1     r1     �1     �1     �1  _   �1  S   2  5   e2  /   �2  Y   �2  p   %3  O   �3  O   �3  F   64  /   }4  1   �4  ;   �4     5               &   6           !                8   1   #          7   )          4   
         3           /       '                      "                ,      .       +   5       0       $       *                    (                %           	          2                    -         BaseDelay

 Fixed amount of time in microseconds, to be used
 as the default delay between any two consecutive
 steps during the animation of the die.

 It may be progressively increased after every step, 
 if Friction is set to a non-zero value (see below).  Friction (or StepDelay)

 Fixed amount of time in microseconds, to fake
 progressive friction during the animation of the
 die.

 The value specified here is repeatedly added to
 the value of BaseDelay (see above) after every 
 animation step, so rolling is progressively slowed
 down.

 The bigger this value is, the bigger is the rate
 of the slowing-down during the progress of the
 animation.  MaxSteps

 Maximum number of times the die will move per roll. 
 The bigger this value is, the longer it takes for the
 animation to get completed.

 A complete rolling-animation will consume this many 
 Steps, something like Frames if it was implemented
 as a true animation, but it is not.

 Thus, if the specified MaxSteps are more than 32
 for the 3D effect or more than 6 for the 2D effect
 (that's how many image-files it takes to implement
 each of those effects) then the animation changes
 direction.

 If the specified MaxSteps are less the than those
 limits, the animation simply stops prematurely.  Result: %d  Spin: %03d | Frame: %03d | Delay: %06ld  This option switches the GUI language according
 to the values of the environment variables LANG 
 and LANGUAGE.

 If they are not set, or if there are no translation
 data available for the locale they define, then the 
 English language is used as fallback.

 The menu-entry is disabled when the program
 starts, because the language dictated by LANG 
 and LANGUAGE is already active, regardless of
 possible fallbacks.
 
 A fallback does not visually disable Engish in the
 menu (the user can select it) so it is clear that
 English was not explicitly selected by the user.

 Please not that both LANG & LANGUAGE must
 be defined before program launch, otherwise a
 fallback to English will occur.

 For example, if LANG is set to "el_GR.UTF-8"
 and LANGUAGE to "el" (both without quotes)
 in the environment, then the program will use
 the Greek language immediately.  When this option is enabled, the program
 outputs extra messages to the stdout &
 stderr streams (this means the standard
 command-line console on most systems).

 In order to see those messages during the 
 execution of the program, you should start 
 it from the command-line.

 On Windows, if you compile the sources
 with the MinGW toolchain without using the 
 linker flag "-mwindows", a console window
 will open automatically at every launch of
 the program (unless of course is already
 launched from the command-line).

 Debugging messages are always displayed 
 in English, since the Windows console does
 not really like UTF-8 (it is possible to make
 it behave properly, but it is not really worth
 the extra effort required by both the user
 and the programmer). ...rolling... <b>Settings</b> Alert Box BaseDelay Debugging mode Default 2D Default 3D File	: %s
Func	: %s
Line	: %d

%s Found invalid GUI elements Free for all Friction GTK+2 Demo - Die GUI is not linked to Core Invalid GUI element (gui->appWindow or gui->dlgAbout) Invalid GUI element (gui->appWindow) Invalid GUI element (gui->menu.itemEnglish) Invalid GUI element (gui->menu.itemEnvLang) Invalid GUI element (gui->menu.itemGreek) Invalid pointer arg (builder) Invalid pointer arg (fnameGlade) Invalid pointer arg (gui or menuItem) Invalid pointer arg (gui) Invalid pointer arg (hslider) MaxSteps No locale environment was found.
ENGLISH is used as fallback language. Roll Small GTK+2 Demo
faking 3D/2D die-animation Use 2D rolling-effect _About _File _Greek _Help _Language _Quit _Roll change the GUI language dynamically check-button has not been properly created detailed information exit program hslider has not been properly created mouseover the slider for details reset 2D settings reset 3D settings slider has not been properly created switch to English switch to Greek toggle between 2D & 3D animation use En_vironment Project-Id-Version: GTK+2 Demo - Die 0.2
Report-Msgid-Bugs-To: 
POT-Creation-Date: 2013-02-04 22:35+0200
PO-Revision-Date: 2013-02-04 22:53+0200
Last-Translator: migf1 <mig_f1@hotmail.com>
Language-Team: migf1 <mig_f1@hotmail.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Language: Greek (Ελληνικά)
X-Generator: Poedit 1.5.5
X-Poedit-SourceCharset: windows-1253
  Καθυστέρηση κίνησης (BaseDelay)

 Χρόνος καθυστέρησης (σε microseconds) μεταξύ δυο
 διαδοχικών βημάτων της κίνησης του ζαριού, ανά ρίψη. 

 Η Καθυστέρηση μπορεί να αυξάνεται σταδιακά σε κάθε 
 βήμα, αν η Τριβή δεν είναι μηδενική (δείτε παρακάτω).  Τριβή (Friction ή StepDelay)

 Χρονικό διάστημα (σε microseconds) για τη δημιουργία
 ψευδαίσθησης τριβης κατά την κίνηση του ζαριού.

 Η τιμή αυτή προστίθεται στην τιμή Καθυστέρησης (δείτε
 παραπάνω) μετά από κάθε βήμα της κίνησης, δίνοντας
 έτσι την εντύπωση πως η κίνηση επιβραδύνεται σταδιακά 
 λόγω τριβής.

 Όσο μεγαλύτερη είναι η Τριβή, τόσο μεγαλώνει ο ρυθμός 
 επιβράδυνσης από κάθε βήμα κίνησης στο επόμενο.   Πλήθος βημάτων (MaxSteps)

 Το συνολικό πλήθος βημάτων της κίνησης, ανά ρίψη ζαριού.
 Όσο μεγαλύτερη είναι αυτή η τιμή, τόσο μεγαλύτερη είναι η
 διάρκεια της κίνησης.

 Σε πραγματικά animations αντί για Βήματα υπάρχουν Καρέ,
 που τα παράγει δυναμικά το animation-engine, ανάλογα με
 την επιθυμητή συνολική διάρκεια. Εμείς δεν χρησιμοποιούμε
 πραγματικό animation.

 Το 3D εφέ κίνησης χρησιμοποιεί 32 εικόνες, ενώ το 2D 6. Αν 
 οριστούν λιγότερα Βήματα, τότε η κίνηση σταματάει πρόωρα.
 Αν οριστούν περισσότερα βήματα, η κίνηση αλλάζει τη φορά
 της ανά 32 βήματα στο 3D εφέ ή ανά 6 βήματα στο 2D εφέ.  Αποτέλεσμα: %d  Βήμα: %03d | Καρέ: %03d | Καθυσ: %06ld  Η επιλογή αυτή γυρίζει τη γλώσσα σε όποια υπαγορεύουν 
 στο σύστημά σας οι μεταβλητές περιβάλλοντος LANG και
 LANGUAGE.

 Αν οι μεταβλητές αυτές δεν έχουν οριστεί ή αν καθορίζουν 
 γλώσσα χωρίς διάθεσιμη μετάφραση, τότε το πρόγραμμα
 χρησιμοποιεί αυτόματα τα Αγγλικά (English).

 Η επιλογή είναι οπτικά απενεργοποιημένη όταν ξεκινάει
 το πρόγραμμα, επειδή έχει φορτωθεί ήδη η γλώσσα που
 ορίζεται μέσω των LANG και LANGUAGE, ακόμα κι όταν
 δεν είναι έγκυρη (οπότε θα έχουν επιλεγεί αυτόματα τα
 Αγγλικά).

 Όταν πραγματοποιείται αυτόματη επιλογή των Αγγλικών
 η επιλογή English παραμένει ενεργοποιημένη μέσα στο
 μενού (μπορεί δηλαδή να επιλεγεί από τον χρήστη) για
 να είναι σαφές πως η τρέχουσα χρήση τους δεν αποτελεί 
 προϊόν συνειδητής επιλογής του χρήστη.

 Για για μην επιλεγούν αυτόματα τα Αγγλικά, θα πρέπει
 και η LANG και η LANGUAGE να προσδιορίζουν γλώσσα
 για την οποία υπάρχει διαθέσιμη μετάφραση.

 Για παράδειγμα, αν η LANG περιέχει "el_GR.UTF-8" και
 η LANGUAGE περιέχει "el" (χωρίς τα εισαγωγικά) τότε
 το πρόγραμμα θα ξεκινήσει από την αρχή με Ελληνικά.  Όταν είναι ενεργοποιημένη αυτή η επιλογή
 το πρόγραμμα τυπώνει έξτρα πληροφορίες
 στα streams stdout & stderr (δηλαδή στην
 κονσόλα, για τα περισσότερα συστήματα).

 Για να μπορείτε να τα βλέπετε πρέπει να
 εκκινήσετε το πρόγραμμα από τη γραμμή
 εντολών.

 Αν είστε σε Windows, μπορείτε να κάνετε
 compile τον κώδικα με το MinGW toolchain
 χωρίς να προσδιορίσετε "-mwindows" στον
 linker. Το εκτελέσιμο που θα παραχθεί θα
 ανοίγει αυτόματα κατά την εκίνησή του κι
 ένα παράθυρο γραμμής εντολών.
 
 Τα μηνύματα αποσφαλμάτωσης είναι πάντα 
 στα Αγγλικά, διότι η κονσόλα των Windows
 δεν τα πάει και πολύ καλά με το UTF-8
 (είναι  εφικτό, αλλά με κόπο τόσο για τον
 χρήστη όσο και για τον προγραμματιστή). ...σε εξέλιξη... <b>Ρυθμίσεις</b> Ειδοποίηση Καθυστέρηση Μηνύματα αποσφαλμάτωσης Προεπιλογές 2D Προεπιλογές 3D Αρχείο  	: %s
Συνάρτ.	: %s
Γραμμή 	: %d

%s Εντοπίστηκαν μη-έγκυρα στοιχεία στο Γραφικό Περιβάλλον. Ελεύθερο για κάθε χρήση Τριβή GTK+2 Demo - Ζάρι Το Γραφικό Περιβάλλον δεν έχει συνδεθεί
με τον κυρίως Πυρήνα του προγράμματος. Μη-έγκυρο γραφικό στοιχείο (gui->appWindow ή gui->dlgAbout). Μη-έγκυρο γραφικό στοιχείο (gui->appWindow). Μη-έγκυρο γραφικό στοιχείο (gui->menu.itemEnglish). Μη-έγκυρο γραφικό στοιχείο (gui->menu.itemEnvLang). Μη-έγκυρο γραφικό στοιχείο (gui->menu.itemGreek). Μη-έγκυρος δείκτης: builder Μη-έγκυρος δείκτης: fnameGlade Μη-έγκυρος δείκτης ορίσματος: gui ή menuItem. Μη-έγκυρος δείκτης ορίσματος: gui Μη-έγκυρος δείκτης ορίσματος: hslider Βήματα Δεν βρέθηκε έγκυρο περιβάλλον εντοπιότητας.
Επιλέχθηκε αυτόματα η ΑΓΓΛΙΚΗ γλώσσα. Ρίψη ζαριού Παράδειγμα Χρήσης του GTK+2
απλοποιημένη 2D & 3D κίνηση ζαριού 2D εφέ κίνησης Σχετικά Αρχείο Ελληνικά Βοήθεια Γλώσσα Έξοδος Ρίψη ζαριού δυναμική αλλαγή γλώσσας του γραφικού περιβάλλοντος Το γραφικό στοιχείο "check-button" δεν είναι έγκυρο. πληροφορίες για το πρόγραμμα τερματισμός προγράμματος Το γραφικό στοιχείο τύπου "hslider" δεν είναι έγκυρο.  ακουμπήστε το ποντίκι στην περιοχή της ρύθμισης για οδηγίες  προεπιλεγμένες ρυθμίσεις του 2D εφέ κίνησης προεπιλεγμένες ρυθμίσεις του 3D εφέ κίνησης Το γραφικό στοιχείο "slider" είναι έγκυρο. αλλαγή γλώσσας σε Αγγλικά αλλαγή γλώσσας σε Ελληνικά εναλλαγή μεταξύ 2D & 3D εφέ κίνησης από Περιβάλλον 