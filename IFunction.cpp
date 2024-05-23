void IFunction(int index, int index1)
{

    bool hasImmediate = false;
    for (char c : code[index])
    {
        if (c == '(')
        {
            hasImmediate = true;
            break;
        }
        if (c == '#')
        {
            break;
        }
    }

    ll rd = 0, rs1 = 0, immediate = 0;

    int i = 0;
    while (code[index][i] != 'x')
    {
        i++;
    }
    i++;
    vector<int> temp;
    while (code[index][i] != ' ' && code[index][i] != ',')
    {
        temp.push_back(code[index][i] - '0');
        i++;
    }
    rd = getnum(temp, 10);
    temp.clear();

    if (!hasImmediate)
    {
        while (code[index][i] != 'x')
        {
            i++;
        }
        i++;
        while (code[index][i] != ' ' && code[index][i] != ',')
        {
            temp.push_back(code[index][i] - '0');
            i++;
        }
        rs1 = getnum(temp, 10);
        temp.clear();
    }
    else
    {

        while (!(code[index][i] >= '0' && code[index][i] <= '9'))
        {
            i++;
        }
        bool isNegativeImmediate = (code[index][i - 1] == '-');
        while (code[index][i] != '(')
        {
            temp.push_back(code[index][i] - '0');
            i++;
        }
        immediate = getnum(temp, 10);
        temp.clear();
        if (isNegativeImmediate)
        {
            immediate = getinver(immediate, 12);
        }
        while (code[index][i] != 'x')
        {
            i++;
        }
        i++;
        while (i < code[index].size() && code[index][i] != ')')
        {
            temp.push_back(code[index][i] - '0');
            i++;
        }
        rs1 = getnum(temp, 10);
        temp.clear();
    }

    int binaryIndex = 0;
    while (Format[index1][binaryIndex] != ' ')
    {
        binaryIndex++;
    }
    binaryIndex++;

    for (int j = 25; j <= 31; j++)
    {
        binary[j] = Format[index1][binaryIndex++] - '0';
    }
    binaryIndex++;
    int rdBitIndex = 24;
    for (int k = 0; k < 5; k++)
    {
        binary[rdBitIndex--] = rd % 2;
        rd /= 2;
    }

    for (int j = 17; j <= 19; j++)
    {
        binary[j] = Format[index1][binaryIndex++] - '0';
    }
    binaryIndex++;
    int rs1BitIndex = 16;
    for (int k = 0; k < 5; k++)
    {
        binary[rs1BitIndex--] = rs1 % 2;
        rs1 /= 2;
    }

    for (int k = 0; k < 12; k++)
    {
        binary[rs1BitIndex--] = immediate % 2;
        immediate /= 2;
    }

    hexa();
}
