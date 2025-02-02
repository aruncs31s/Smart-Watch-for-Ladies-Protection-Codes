def test():
    some_list = ["hi", "help", "but"]

    if 4 not in some_list:
        print("yes")
    if 6 in some_list:
        print("yes yes")

    if "help" in some_list:
        print("hi yes")


def detect_help(theWords):
    if "help" in theWords:
        return True
    else:
        return False


if __name__ == "__main__":
    # test()
    detect_help(["help"]) and print("hi")
