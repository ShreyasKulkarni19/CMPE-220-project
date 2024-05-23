void SFunction(int index, int index1)
{

    int codeSize = code[index].size();
    int formatSize = Format[index1].size();

    ll rs1 = 0, rs2 = 0, immediate = 0;

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
    rs2 = getnum(temp, 10);
    temp.clear();

    while (!(code[index][i] >= '0' && code[index][i] <= '9'))
    {
        i++;
    }
    bool isNegativeImmediate = (i - 1 >= 0 && code[index][i - 1] == '-');
    while (code[index][i] != '(')
    {
        temp.push_back(code[index][i] - '0');
        if (code[index][i] == 'x')
        {

            immediate = 1;
        }
        i++;
    }
    immediate = (immediate == 1) ? gethex(temp) : getnum(temp, 10);
    if (isNegativeImmediate)
    {
        immediate = getinver(immediate, 12);
    }
    temp.clear();

    while (code[index][i] != 'x')
    {
        i++;
    }
    i++;
    while (i < codeSize && code[index][i] != ')')
    {
        temp.push_back(code[index][i] - '0');
        i++;
    }
    rs1 = getnum(temp, 10);
    temp.clear();

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
    int rs2BitIndex = 24;
    for (int k = 0; k < 5; k++)
    {
        binary[rs2BitIndex--] = rs2 % 2;
        rs2 /= 2;
    }

    for (int k = 0; k < 12; k++)
    {
        binary[rs2BitIndex--] = immediate % 2;
        immediate /= 2;
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

    for (int j = 6; j >= 0; j--)
    {
        binary[j] = 0;
    }

    hexa();
}
