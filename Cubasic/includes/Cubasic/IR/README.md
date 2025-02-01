## What is IR

The IR in this case takes all the Tokens and condenses them into a flat stream.

This removes every function and generates a sudo-variable for every value.

The follow code
```
FUNCTION Main()
    PRINT "Hello, Cubasic!"
    DIM arr(10)
    FOR i IN 0 TO 9
        SET arr[i] = i * 2
        NEXT i
    IF arr[5] > 10 THEN
        PRINT "Value is greater than 10"
    ELSE
        PRINT "Value is 10 or less"
    ENDIF
END
```

would turn into
```
StringLiteral1 = "Hello, Cubasic!"
arrayDef1_Value1 = 0
arrayDef1_Value2 = 0
arrayDef1_Value3 = 0
arrayDef1_Value4 = 0
arrayDef1_Value5 = 0
arrayDef1_Value6 = 0
arrayDef1_Value7 = 0
arrayDef1_Value8 = 0
arrayDef1_Value9 = 0
arrayDef1_Value10 = 0
loopIndexDef_i = 0
```