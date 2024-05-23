void RFunction(int index, int index1)
{
    // Determine the size of the instruction and format
    int codeSize = code[index].size();
    int formatSize = Format[index1].size();

    // Variables for instruction fields
    ll rd, rs1, rs2;

    // Extracting fields from the instruction code
    int i = 0;
    i++; // Skip 'x' from XOR instruction
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

    // Extracting rs1
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

    // Extracting rs2
    while (code[index][i] != 'x')
    {
        i++;
    }
    i++;
    while (i < codeSize && code[index][i] != ' ' && code[index][i] != '#' && code[index][i] != ',')
    {
        temp.push_back(code[index][i] - '0');
        i++;
    }
    rs2 = getnum(temp, 10);
    temp.clear();

    // Populate binary array with instruction fields
    int binaryIndex = 0;
    while (Format[index1][binaryIndex] != ' ')
    {
        binaryIndex++;
    }
    binaryIndex++;

    // Encoding rs2 field
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

    // Encoding rd field
    for (int j = 17; j <= 19; j++)
    {
        binary[j] = Format[index1][binaryIndex++] - '0';
    }
    binaryIndex++;
    int rdBitIndex = 16;
    for (int k = 0; k < 5; k++)
    {
        binary[rdBitIndex--] = rd % 2;
        rd /= 2;
    }

    // Encoding rs1 field
    for (int j = 6; j >= 0; j--)
    {
        binary[j] = Format[index1][binaryIndex++] - '0';
    }

    // Convert binary to hexadecimal
    hexa();
}
