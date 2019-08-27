
def sth( param0):# {{{
    return hex(isInt(param0))
    # }}}
    

def isInt(var):# {{{
    if isinstance(var, int):
        return var
    if isinstance(var, list) and len(var) == 1:
        return var[0]
    try:
        return int(var)
    except ValueError:
        print("Not know Command or number")
        return 0
    # }}}

def fillLEDset(setlist, command):# {{{
    """Filling list from arrey and adding command"""
    return [
          isInt(setlist[5]),
          isInt(setlist[4]), 
          isInt(setlist[3]), 
          isInt(setlist[2]), 
          command 
          ] 
    # }}}
        
        
