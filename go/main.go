package main

import (
    "bytes"
    "image/jpeg"
    "io/ioutil"
    "os"
    "strconv"
)

func main() {
    data, _ := ioutil.ReadFile(os.Args[1])
    iterations, _ := strconv.Atoi(os.Args[2])
    failure := false

    for i := 0; i < iterations; i++ {
        _, err := jpeg.Decode(bytes.NewReader(data))
        failure = failure || err != nil
    }

    if failure {
        os.Exit(1)
    }
}
