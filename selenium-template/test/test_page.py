from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By

from contextlib import contextmanager
from selenium.common.exceptions import NoSuchElementException
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support.expected_conditions import staleness_of, presence_of_element_located
from pytest import raises
from pathlib import Path
import os


def construct_headless_chrome_driver():
    options = Options()
    options.add_argument("--disable-extensions")
    options.add_argument("--disable-gpu")
    options.add_argument("--no-sandbox")
    options.add_argument("--headless")
    return webdriver.Chrome(options=options)


def get_landing_page_url():
    test_dir = os.getcwd()
    index_path = os.path.join(test_dir, "..", "page", "index.html")
    index_uri = Path(index_path).as_uri()
    return index_uri

# As demonstrated in the linked web page from the course assignment
@contextmanager
def wait_for_page_load(driver, timeout=30):
    old_page = driver.find_element_by_tag_name('html')
    yield
    WebDriverWait(driver, timeout).until( staleness_of(old_page) )


def test_nonsecret_scenario():
    landing_page = get_landing_page_url()
    driver = construct_headless_chrome_driver()
    driver.get(landing_page)
    
    name = "myname"
    food = "sushi"
    secret = "idk"

    driver.find_element_by_id("preferredname").send_keys(name)
    driver.find_element_by_id("food").send_keys(food)
    driver.find_element_by_id("secret").send_keys(secret)
    driver.find_element_by_id("submit").click()
    
    assert "response.html" in driver.current_url
    assert name == driver.find_element_by_id("thankname").get_attribute('innerHTML')
    assert food == driver.find_element_by_id("foodploy").get_attribute('innerHTML')
    assert len(driver.find_element_by_id("secrets").find_elements_by_xpath(".//button")) == 0

    driver.quit()


def test_secret_scenario():
    landing_page = get_landing_page_url()
    driver = construct_headless_chrome_driver()
    driver.get(landing_page)
    
    name = "myname"
    food = "sushi"
    secret = "magic"

    driver.find_element_by_id("preferredname").send_keys(name)
    driver.find_element_by_id("food").send_keys(food)
    driver.find_element_by_id("secret").send_keys(secret)
    driver.find_element_by_id("submit").click()
    
    assert "response.html" in driver.current_url
    assert name == driver.find_element_by_id("thankname").get_attribute('innerHTML')
    assert food == driver.find_element_by_id("foodploy").get_attribute('innerHTML')
    assert len(driver.find_element_by_id("secrets").find_elements_by_xpath(".//button")) == 1

    driver.find_element_by_id("secretButton").click()    
    WebDriverWait(driver, 30).until(presence_of_element_located((By.ID, 'secret')))
    
    assert "secret.html" in driver.current_url
    assert name == driver.find_element_by_id("thankname").get_attribute('innerHTML')
    assert secret == driver.find_element_by_id("secret").get_attribute('innerHTML')

    driver.quit()