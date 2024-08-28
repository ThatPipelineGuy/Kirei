# Bash Script to Check and Install xmake on Linux/macOS

# Check if xmake is installed
if ! command -v xmake &> /dev/null
then
    echo "xmake is not installed. Installing xmake..."
    # Install xmake
    curl -fsSL https://xmake.io/shget.text | bash
else
    echo "xmake is already installed."
fi
