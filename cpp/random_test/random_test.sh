while true; do
    python3 ./generate.py > random.in
    A=$(./a.out < random.in)
    B=$(./b.out < random.in)
    if [ $A != $B ]; then
        echo "----------------------------------------"
        echo "Wrong Answer"
        echo "[test case] "
        cat random.in
        echo "[./a.out] "
        echo $A
        echo "[./b.out] "
        echo $B
        echo "----------------------------------------"
    fi
done
