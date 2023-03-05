struct GSInput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

struct GSOutput
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

[maxvertexcount(6)]
void main(triangle GSInput input[3], inout LineStream<GSOutput> OutputStream)
{
    // Generate two lines for each edge of the triangle
    for (int i = 0; i < 3; i++)
    {
        int j = (i + 1) % 3;

        // Set the line color to black
        GSOutput output1;
        output1.position = input[i].position;
        output1.color = float4(0, 0, 0, 1);

        GSOutput output2;
        output2.position = input[j].position;
        output2.color = float4(0, 0, 0, 1);

        // Output the line vertices
        OutputStream.Append(output1);
        OutputStream.Append(output2);
    }
}