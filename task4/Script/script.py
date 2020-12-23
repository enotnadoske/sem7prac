import subprocess
import os
import time
import shutil


main_dir = os.getcwd()

for i in range(10):
    for it in range(10):
        if os.path.exists(main_dir + f"/series{i}_run{it}"):
            shutil.rmtree(main_dir + f"/series{i}_run{it}")
        os.makedirs(f"series{i}_run{it}")
        os.chdir(main_dir + f"/series{i}_run{it}")
        start_time = time.time()
        subprocess.check_call([main_dir + f"/a.out {i}  {it}"], shell=True)
        end_time = time.time()
        f = open(f'series_{i}_run_{it}_time.txt', "a")
        f.write('\n')
        f.write(str(end_time - start_time))
        f.close()

        os.chdir(main_dir)

        time.sleep(1)
