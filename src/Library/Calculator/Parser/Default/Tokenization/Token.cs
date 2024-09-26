// Adam Dernis 2024

namespace Calculator.Parser.Default.Tokenization;

public class Token(string tokenString, TokenType type, int position)
{
    public string TokenString { get; } = tokenString;

    public TokenType TokenType { get; } = type;

    public int Position { get; } = position;

    public static bool operator ==(Token left, char right)
        => left.TokenString.Length is 1 && left.TokenString[0] == right;

    public static bool operator !=(Token left, char right) => !(left == right);
}
