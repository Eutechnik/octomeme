def welcome():
    print "Welcome!"
    print "Would you like to play a game?"
    response = raw_input("Type yes or no and hit 'Enter'.").lower()
    if response == "yes" or response == "y" or response == "Y":
        print "This is the Verbal Abuse Room, you heap of parrot droppings!"
    elif response == "no" or response == "N" or response == "No" or response == "n":
        print "Jibba Jabba jooooooo. Octomeme"
    else:
        print "What? I didn't understand! Try again"
        welcome()

welcome()