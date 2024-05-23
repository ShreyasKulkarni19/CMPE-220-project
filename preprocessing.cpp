// Preprocess the code to replace pseudo instructions
void preprocess()
{
    for (int codeIndex = 0; codeIndex < code.size(); codeIndex++)
    {
        int codeSize = code[codeIndex].size();
        for (int charIndex = 1; charIndex < codeSize; charIndex++)
        {
            char currentChar = code[codeIndex][charIndex];
            if ((code[codeIndex][charIndex - 1] == ' ' || code[codeIndex][charIndex - 1] == '(' || code[codeIndex][charIndex - 1] == ',') &&
                currentChar == 's' && charIndex + 2 < codeSize && code[codeIndex][charIndex + 1] == 'p' &&
                (code[codeIndex][charIndex + 2] == ' ' || code[codeIndex][charIndex + 2] == ',' || code[codeIndex][charIndex + 2] == ')'))
            {
                code[codeIndex][charIndex] = 'x';
                code[codeIndex][charIndex + 1] = '2';
            }
        }
    }
}

// Process Load Address (la) pseudo command
void processLA(int index)
{
    int i = 0;
    while (codeinit[index][i] != 'x')
        i++;
    i++;
    string registerName;
    while (codeinit[index][i] != ' ')
        registerName += codeinit[index][i++];

    // Generate 'auipc' instruction
    string ins = "auipc x" + registerName + " 65536";
    code.push_back(ins);

    // Calculate label address relative to current PC
    int currentPC = code.size() * 4 - 4 + START;
    while (codeinit[index][i] == ' ')
        i++;
    string labelType;
    while (i < codeinit[index].size() && codeinit[index][i] != ' ')
        labelType += codeinit[index][i++];
    ll labelAddress = 0;
    for (int j = 0; j < datalabel.size(); j++)
    {
        if (labelType.compare(datalabel[j].name) == 0)
        {
            labelAddress = datalabel[j].position - currentPC;
            break;
        }
    }
    string labelAdd = to_string(labelAddress);

    // Generate 'addi' instruction
    ins = "addi x" + registerName + " x" + registerName + " " + labelAdd;
    code.push_back(ins);
}

// Process Load Word (lw) pseudo command
void processLW(string type, int index, ll pos)
{
    ll currentPC = code.size() * 4 + START;
    int i = 0;
    while (codeinit[index][i] != 'x')
        i++;
    i++;
    string registerName;
    while (codeinit[index][i] != ' ')
        registerName += codeinit[index][i++];
    currentPC = pos - currentPC;

    // Generate 'auipc' instruction
    string ins = "auipc x" + registerName + " 65536";
    code.push_back(ins);

    // Calculate offset relative to current PC
    string labelAdd = to_string(currentPC);

    // Generate load instruction
    ins = type + " x" + registerName + " " + labelAdd + "(x" + registerName + ")";
    code.push_back(ins);
}
